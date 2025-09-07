#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QProcess>
#include <QDebug>

class OpenOCDRunner : public QWidget {
    Q_OBJECT

public:
    OpenOCDRunner(QWidget *parent = nullptr) : QWidget(parent) {
        auto *layout = new QVBoxLayout(this);

        startButton = new QPushButton("Start OpenOCD", this);
        stopButton = new QPushButton("Stop OpenOCD", this);
        outputBox = new QTextEdit(this);
        outputBox->setReadOnly(true);

        layout->addWidget(startButton);
        layout->addWidget(stopButton);
        layout->addWidget(outputBox);

        process = new QProcess(this);

        // Connect process signals
        connect(startButton, &QPushButton::clicked, this, &OpenOCDRunner::startOpenOCD);
        connect(stopButton, &QPushButton::clicked, this, &OpenOCDRunner::stopOpenOCD);
        connect(process, &QProcess::readyReadStandardOutput, this, &OpenOCDRunner::readOutput);
        connect(process, &QProcess::readyReadStandardError, this, &OpenOCDRunner::readError);
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, &OpenOCDRunner::processFinished);
    }

private slots:
    void startOpenOCD() {
        if (process->state() == QProcess::NotRunning) {
            outputBox->append("Starting OpenOCD...");
            QString program = "openocd";
            QStringList args;
            args << "-f" << "/home/quangnm/Documents/GitHub/seer/openocd/tcl/interface/jlink.cfg"
                 << "-f" << "/home/quangnm/Documents/GitHub/seer/openocd/tcl/target/stm32f4x.cfg";

            process->start(program, args);
        } else {
            outputBox->append("OpenOCD is already running.");
        }
    }

    void stopOpenOCD() {
        if (process->state() != QProcess::NotRunning) {
            process->kill();
            outputBox->append("OpenOCD stopped.");
        }
    }

    void readOutput() {
        outputBox->append(QString::fromLocal8Bit(process->readAllStandardOutput()));
    }

    void readError() {
        outputBox->append(QString::fromLocal8Bit(process->readAllStandardError()));
    }

    void processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        Q_UNUSED(exitStatus);
        outputBox->append(QString("OpenOCD exited with code %1").arg(exitCode));
    }

private:
    QPushButton *startButton;
    QPushButton *stopButton;
    QTextEdit *outputBox;
    QProcess *process;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OpenOCDRunner runner;
    runner.setWindowTitle("OpenOCD Runner");
    runner.resize(600, 400);
    runner.show();

    return app.exec();
}
