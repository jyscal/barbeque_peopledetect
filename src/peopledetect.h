#ifndef PEOPLEDETECT_H
#define PEOPLEDETECT_H

#include <opencv2/core/utility.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <bbque/bbque_exc.h>
#include <string>

class Detector {
    enum Mode { Default, Daimler } m;
    cv::HOGDescriptor hog, hog_d;
public:
    Detector();
    void toggleMode() { m = (m == Default ? Daimler : Default); }
    std::string modeName() const { return (m == Default ? "Default" : "Daimler"); }

    std::vector<cv::Rect> detect(cv::InputArray img);
    void adjustRect(cv::Rect & r) const;
};

class PeopleDetect : public bbque::rtlib::BbqueEXC {
    std::string filename_;
    cv::VideoCapture cap_;
    int camera_;
    Detector detector_;
    cv::Mat frame_;

    void show_frame(std::vector<cv::Rect> &found, int64 elapsed_millis);

public:
    PeopleDetect(std::string const &name,
                 std::string const &recipe,
                 RTLIB_Services_t *rtlib,
                 int camera, std::string filename);
    virtual ~PeopleDetect();
    virtual RTLIB_ExitCode_t onSetup() override;
    virtual RTLIB_ExitCode_t onConfigure(int8_t awm_id) override;
    virtual RTLIB_ExitCode_t onRun() override;
    virtual RTLIB_ExitCode_t onMonitor() override;
    virtual RTLIB_ExitCode_t onSuspend() override;
};

#endif
