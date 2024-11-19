#include "timer/timer_manager.h"






using namespace duck::timer;

long g_frame_count = 0;

void isp_handle(long* frame_count)
{
    *frame_count = *frame_count + 1;
}

void fps_handle(long* args) 
{
    static long pre_frame_count = 0;
    long frame_count = *args;
    long fps = (frame_count > pre_frame_count) ? (frame_count - pre_frame_count) : (pre_frame_count - frame_count);
    LOG(INFO) << "fps=" << fps;
    pre_frame_count = frame_count;
}

void hello()
{
    static int count = 0;
    LOG(INFO) << "hello=" << count;
    count++;
}


int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);

    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;


    TimerManager manager(1);


    manager.submit(33, -1, isp_handle, &g_frame_count);
    manager.submit(1000, -1, fps_handle, &g_frame_count);

    manager.start(); 

    std::this_thread::sleep_for(std::chrono::seconds(5));

    manager.submit(500, 5, hello);

    std::cout << "wait key..." << std::endl;
    std::getchar(); 
 
    manager.stop(); 

    std::cout << "bye!" << std::endl;

    return 0;
}



















