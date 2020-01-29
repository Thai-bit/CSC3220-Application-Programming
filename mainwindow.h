#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_sQueenRadioButton_clicked();

    void on_sKingRadioButton_clicked();

    void on_aQueenRadioButton_clicked();

    void on_aKingRadioButton_clicked();



    void on_rightArrowButton_clicked();

    void on_leftArrorwButton_clicked();

    void on_nextButton_clicked();

    void on_backButton_clicked();

    void on_confirmButton_clicked();

    void on_dateLengthSpinBox_valueChanged(int arg1);

    void on_parkingCheckBox_clicked(bool checked);

    void on_guestSpinBox_valueChanged();

    void on_childrenSpinbox_valueChanged();


    void on_masterCardButton_clicked();

    void on_visaButton_clicked();

    void on_americanButton_clicked();

    void on_discoverButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap imageSqueen;
    QPixmap imageSqueen1;
    QPixmap imageSking;
    QPixmap imageSking1;
    QPixmap imageAqueen;
    QPixmap imageAqueen1;
    QPixmap imageAking;
    QPixmap imageAking1;;
    bool isStandardQueenChecked;
    bool isStandardKingChecked;
    bool isAtriumQueenChecked;
    bool isAtriumKingChecked;
    string customerName;
    int roomType;
    int numNights;
    bool parkingNeeded;
    public:
    string GetCustomerName();
    void SetCustomerName(string name);
    int GetRoomType();
    void SetRoomType(int type);
    int GetNumNights();
    void SetNumNights(int nights);
    bool GetParkingNeeded();
    void SetParkingNeeded(bool needed);
    double CalculateCost();
    void CurrentChoice();
    double CalculateCostTax();


    void imageInput();

};
#endif // MAINWINDOW_H
