#include "utils/timer.h"






using namespace duck::utils;

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


int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);

    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;

    Timer isp_timer(33);
    Timer fps_timer(1000);

    isp_timer.submit(isp_handle, &g_frame_count);
    fps_timer.submit(fps_handle, &g_frame_count);

    isp_timer.start();
    fps_timer.start();

    std::cout << "wait key..." << std::endl;
    std::getchar(); 
 
    isp_timer.stop();
    fps_timer.stop();

    std::cout << "bye!" << std::endl;

    return 0;
}



















