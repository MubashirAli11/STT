#include <cstdio>
#include <cstdlib>
#include <vector>
#include <signal.h>
#include <ctype.h>

#include <caffe/caffe.hpp>
#include <caffe/solver.hpp>
#include <caffe/solver_factory.hpp>
#include <caffe/sgd_solvers.hpp>
#include <caffe/util/io.hpp>
#include <caffe/layers/memory_data_layer.hpp>
#include <caffe/layers/sigmoid_cross_entropy_loss_layer.hpp>
#include <caffe/layers/euclidean_loss_layer.hpp>
#include <caffe/layers/inner_product_layer.hpp>
#include <caffe/util/db_lmdb.hpp>
#include <caffe/net.hpp>
#include <CppUTest/TestHarness.h>

int requested_to_exit = 0;

using namespace std;
using namespace caffe;

double
get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    double time_in_sec = (tv.tv_sec) + ((double) tv.tv_usec * (double) 10e-7);
    return time_in_sec;
}


vector<caffe::Datum>
build_datum_vector(double x, double label)
{
    vector<caffe::Datum> datums;
    caffe::Datum d;

    d.set_channels(1);
    d.set_height(1);
    d.set_width(1);
    d.set_label(label);
    d.add_float_data(x);

    datums.push_back(d);
    return datums;
}


void
shutdown(int sign)
{
    if (sign == SIGINT) {
        printf("Exit requested\n");
        requested_to_exit = 1;
    }
}

TEST_GROUP(CaffeTest)
{

    void setup() override {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();

    }
    void teardown() override {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

TEST(CaffeTest, run_caffe_example)
{
    signal(SIGINT, shutdown);

    boost::shared_ptr<caffe::Solver<float>> solver;
    boost::shared_ptr<caffe::Net<float>> net ;

    caffe::SolverParameter solver_param;

    caffe::ReadProtoFromTextFileOrDie("solver.prototxt", &solver_param);
    solver.reset(caffe::SolverRegistry<float>::CreateSolver(solver_param));

    net = solver->net();

    boost::shared_ptr<caffe::MemoryDataLayer<float>> input = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<float>>(net->layer_by_name("input"));
    boost::shared_ptr<caffe::MemoryDataLayer<float>> reset = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<float>>(net->layer_by_name("reset"));
    boost::shared_ptr<caffe::MemoryDataLayer<float>> target = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<float>>(net->layer_by_name("target"));

    int epoch = 1;
    int sample = 1;

    double total_error_per_epoch = DBL_MAX;

    double max_error = 0;
    int just_test = 0;

    double sampling_frequency = 1.0 / 20.0; // Hz
    double period_duration = 1.0; // second
    double curr_time = 0.0;

    double x;

    while (1) {
        if (requested_to_exit) {
            break;
        }

        x = (2 * M_PI * curr_time) / period_duration;
        double desired_y = sin(x);

        if (sample == 1) {
            reset->AddDatumVector(build_datum_vector(0, 0));
        }

        else {
            reset->AddDatumVector(build_datum_vector(1, 0));
        }

        input->AddDatumVector(build_datum_vector(x, 0));
        target->AddDatumVector(build_datum_vector(desired_y, 0));

        float loss;

        if (!just_test) {
            solver->Step(10);

            assert(!isnan(net->layer_by_name("lstm")->blobs().front()->data_at(1, 0, 0, 0)));
            assert(!isnan(net->layer_by_name("fc")->blobs().front()->data_at(1, 0, 0, 0)));

            loss = net->blob_by_name("loss")->cpu_data()[0];
        }

        else {
            net->Forward(&loss);
        }

        double estimated_y = net->blob_by_name("fc")->cpu_data()[0];
        float diff = fabs(desired_y - estimated_y);

        if (just_test) {
            printf("TEST EPOCH %d SAMPLE %d LOSS: %.4f DES: %.4f EST: %.4f ERR: %.4f\n",
                   epoch, sample, loss,
                   desired_y, estimated_y, diff
                  );
        }

        else {
            printf("TRAIN EPOCH %d SAMPLE %d LOSS: %.4f DES: %.4f EST: %.4f ERR: %.4f\n",
                   epoch, sample, loss,
                   desired_y, estimated_y, diff
                  );
        }

        fflush(stdout);
        total_error_per_epoch += diff;

        if (diff > max_error) {
            max_error = diff;
        }

        sample++;
        curr_time += sampling_frequency;

        if (curr_time > period_duration) {
            if (just_test)
                printf("REPORT EPOCH %d total_err: %.4lf max_err: %.4lf\n",
                       epoch, total_error_per_epoch, max_error);

            //fprintf(stderr, "NEW\n");
            //getchar();

            if (just_test && total_error_per_epoch < 0.) {
                break;
            }

            sample = 1;
            epoch++;
            total_error_per_epoch = 0.0;
            max_error = 0.0;
            curr_time = 0.0;
            just_test = !just_test;
        }
    }
}
TEST(CaffeTest, create_lmdb_for_sin_function)
{
    using namespace caffe::db;
    LMDB lmdb;
    lmdb.Open("test_lmdb", Mode::NEW);
    LMDBTransaction* transaction = lmdb.NewTransaction();
    size_t count = 0;

    for (double x = 0.0; x <= 2.0 * M_PI; x += .001) {
        transaction->Put(std::to_string(count++), build_datum_vector(x, 0).back().SerializeAsString());
    }

    transaction->Commit();
    lmdb.Close();
}
TEST(CaffeTest, read_lmdb_for_sin_function)
{
    using namespace caffe::db;
    LMDB lmdb;
    lmdb.Open("test_lmdb", Mode::READ);
    LMDBCursor* cursor = lmdb.NewCursor();
    caffe::Datum d;

    for (cursor->SeekToFirst(); cursor->valid(); cursor->Next()) {
        d.ParseFromString(cursor->value());
        std::cout << cursor->key() << " " << d.float_data(0) << std::endl;
    }

    lmdb.Close();
}
TEST(CaffeTest, caffe_from_scratch)
{

    Caffe::set_mode(Caffe::CPU);

    LayerParameter data_layer;
    data_layer.set_name("data");
    data_layer.set_type("Data");

    auto data_param = data_layer.mutable_data_param();

    data_layer.add_top("data");
    data_layer.add_top("label");

    data_param->set_backend(DataParameter_DB_LMDB);
    data_param->set_batch_size(1);
    data_param->set_source("test_lmdb");

    NetParameter net_parameters;
    net_parameters.set_name("sin_approximation");
    *(net_parameters.add_layer()) = data_layer;


    SolverParameter solver_parameter;
    *(solver_parameter.mutable_net_param()) = net_parameters;
    solver_parameter.set_lr_policy("step");
    solver_parameter.set_base_lr(0.1);

    //boost::shared_ptr<Solver<double>> solver {SolverRegistry<double>::CreateSolver(solver_parameter)};
    SGDSolver<double> solver(solver_parameter);

    solver.Step(10);
    solver.Solve();

    boost::shared_ptr<Net<double>> net(solver.net());
    std::cout << net->blob_by_name("data")->mutable_cpu_data()[10] << std::endl;

}
