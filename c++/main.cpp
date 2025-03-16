#include <opencv2/opencv.hpp>
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <iostream>
#include <string>

class VideoEditor : public QWidget {
    Q_OBJECT

public:
    VideoEditor(QWidget *parent = nullptr);

private slots:
    void loadVideo();
    void trimVideo();
    void cropVideo();
    void applyFilter();
    void addText();
    void changeSpeed();
    void saveVideo();

private:
    cv::VideoCapture cap;
    cv::VideoWriter writer;
    std::string filename;
    int startFrame, endFrame;
    int cropX, cropY, cropWidth, cropHeight;
    double speedFactor;
    QString textOverlay;
};

VideoEditor::VideoEditor(QWidget *parent) : QWidget(parent) {
    QPushButton *loadBtn = new QPushButton("Load Video");
    QPushButton *trimBtn = new QPushButton("Trim Video");
    QPushButton *cropBtn = new QPushButton("Crop Video");
    QPushButton *filterBtn = new QPushButton("Apply Filter");
    QPushButton *textBtn = new QPushButton("Add Text");
    QPushButton *speedBtn = new QPushButton("Change Speed");
    QPushButton *saveBtn = new QPushButton("Save Video");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(loadBtn);
    layout->addWidget(trimBtn);
    layout->addWidget(cropBtn);
    layout->addWidget(filterBtn);
    layout->addWidget(textBtn);
    layout->addWidget(speedBtn);
    layout->addWidget(saveBtn);
    setLayout(layout);

    connect(loadBtn, &QPushButton::clicked, this, &VideoEditor::loadVideo);
    connect(trimBtn, &QPushButton::clicked, this, &VideoEditor::trimVideo);
    connect(cropBtn, &QPushButton::clicked, this, &VideoEditor::cropVideo);
    connect(filterBtn, &QPushButton::clicked, this, &VideoEditor::applyFilter);
    connect(textBtn, &QPushButton::clicked, this, &VideoEditor::addText);
    connect(speedBtn, &QPushButton::clicked, this, &VideoEditor::changeSpeed);
    connect(saveBtn, &QPushButton::clicked, this, &VideoEditor::saveVideo);
}

void VideoEditor::loadVideo() {
    filename = QFileDialog::getOpenFileName(this, "Open Video").toStdString();
    cap.open(filename);
    if (!cap.isOpened()) {
        QMessageBox::critical(this, "Error", "Failed to open video file.");
    }
}

void VideoEditor::trimVideo() {
    startFrame = 10; // Example start frame
    endFrame = 100;  // Example end frame
}

void VideoEditor::cropVideo() {
    cropX = 100;
    cropY = 100;
    cropWidth = 400;
    cropHeight = 300;
}

void VideoEditor::applyFilter() {
    cv::Mat frame;
    while (cap.read(frame)) {
        cv::convertScaleAbs(frame, frame, 1.2, 50); // Basic brightness and contrast
    }
}

void VideoEditor::addText() {
    textOverlay = "Sample Text";
    cv::Mat frame;
    while (cap.read(frame)) {
        cv::putText(frame, textOverlay.toStdString(), cv::Point(50, 50),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
}

void VideoEditor::changeSpeed() {
    speedFactor = 1.5; // Example speed increase
}

void VideoEditor::saveVideo() {
    cv::Mat frame;
    writer.open("output_video.mp4", cv::VideoWriter::fourcc('M','J','P','G'),
                cap.get(cv::CAP_PROP_FPS) * speedFactor,
                cv::Size(cropWidth, cropHeight));

    cap.set(cv::CAP_PROP_POS_FRAMES, startFrame);
    for (int i = startFrame; i <= endFrame && cap.read(frame); ++i) {
        cv::Mat croppedFrame = frame(cv::Rect(cropX, cropY, cropWidth, cropHeight));
        writer.write(croppedFrame);
    }
    writer.release();
    QMessageBox::information(this, "Done", "Video saved successfully!");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    VideoEditor editor;
    editor.show();
    return app.exec();
}

#include "main.moc"
