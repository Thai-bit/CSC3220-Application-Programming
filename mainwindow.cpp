#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //date calendar
    ui->dateEdit->setDate(QDate::currentDate());
    parkingNeeded = false;
    //start with one night reservation
    numNights = 1;
    //set room value to zero
    SetRoomType(0);
    // credit card dropbox
    for(int i = 1; i <= 12; i++){
        if(i < 10){
        ui->monthComboBox->addItem("0" + QString::number(i));
        } else {
            ui->monthComboBox->addItem(QString::number(i));
        }
    }
    for(int i = QDate::currentDate().year(); i <= QDate::currentDate().year() + 7; i++){
        ui->yearComboBox->addItem(QString::number(i));
    }

    }




MainWindow::~MainWindow()
{
    delete ui;
}



// condition for standard queen room
void MainWindow::on_sQueenRadioButton_clicked()
{
    imageInput();
    ui->imageLabel1->setPixmap(imageSqueen);
    ui->imageLabel2->setPixmap(imageSqueen);
    SetRoomType(1);
    ui->totalEstimateLabel->setText("$" + QString::number(CalculateCost()));
    ui->guestSpinBox->setValue(1);
    ui->childrenSpinbox->setValue(0);
    ui->guestSpinBox->setMaximum(4);
    ui->childrenSpinbox->setMaximum(4);
    ui->roomTypeLabel->setText("Standard 2-Queen Room");
    CurrentChoice();
}

// condition for standard king room
void MainWindow::on_sKingRadioButton_clicked()
{
    imageInput();
    ui->imageLabel1->setPixmap(imageSking);
    ui->imageLabel2->setPixmap(imageSking);
    SetRoomType(3);
    ui->totalEstimateLabel->setText("$" + QString::number(CalculateCost()));
    ui->guestSpinBox->setValue(1);
    ui->childrenSpinbox->setValue(0);
    ui->guestSpinBox->setMaximum(3);
    ui->childrenSpinbox->setMaximum(3);
    ui->roomTypeLabel->setText("Standard 1-King Room");
    CurrentChoice();
}


// condition for atrium queen room
void MainWindow::on_aQueenRadioButton_clicked()
{
    imageInput();
    ui->imageLabel1->setPixmap(imageAqueen);
    ui->imageLabel2->setPixmap(imageAqueen);
    SetRoomType(2);
    ui->totalEstimateLabel->setText("$" + QString::number(CalculateCost()));
    ui->guestSpinBox->setValue(1);
    ui->childrenSpinbox->setValue(0);
    ui->guestSpinBox->setMaximum(4);
    ui->childrenSpinbox->setMaximum(4);
    ui->roomTypeLabel->setText("Atrium 2-Queen Room");
    CurrentChoice();
}

//  contion for atrium bed room
void MainWindow::on_aKingRadioButton_clicked()
{
    imageInput();
    ui->imageLabel1->setPixmap(imageAking);
    ui->imageLabel2->setPixmap(imageAking);
    SetRoomType(4);
    ui->totalEstimateLabel->setText("$" + QString::number(CalculateCost()));
    ui->guestSpinBox->setValue(1);
    ui->childrenSpinbox->setValue(0);
    ui->guestSpinBox->setMaximum(3);
    ui->childrenSpinbox->setMaximum(3);
    ui->roomTypeLabel->setText("Atrium 1-King Room");
    CurrentChoice();
}

// right arrow to switch picture
void MainWindow::on_rightArrowButton_clicked()
{
     ui->stackedWidget2->setCurrentIndex(1);
     imageInput();

      if(ui->sQueenRadioButton->isChecked()){
            ui->imageLabel2->setPixmap(imageSqueen1);
}     else if(ui->sKingRadioButton->isChecked()){
    ui->imageLabel2->setPixmap(imageSking1);
    } else if (ui->aQueenRadioButton->isChecked()){
                    ui->imageLabel2->setPixmap(imageAqueen1);
    } else if (ui->aKingRadioButton->isChecked()){
        ui->imageLabel2->setPixmap(imageAking1);
    }
}

// left arrow to switch picture
void MainWindow::on_leftArrorwButton_clicked()
{
    ui->stackedWidget2->setCurrentIndex(0);
    imageInput();
      if(ui->sQueenRadioButton->isChecked()){
            ui->imageLabel1->setPixmap(imageSqueen);
    } else if(ui->sKingRadioButton->isChecked()){
                   ui->imageLabel1->setPixmap(imageSking);
    } else if(ui->aQueenRadioButton->isChecked()){
            ui->imageLabel1->setPixmap(imageAqueen);

    } else if(ui->aKingRadioButton->isChecked()) {
            ui->imageLabel2->setPixmap(imageAking);
        }
}

// summary of the calculated prices and fees
void MainWindow::CurrentChoice(){
    ui->taxLabel->setText("$" + QString::number(CalculateCostTax()));
    double parkingFee = 0;
    if(GetParkingNeeded()){
         parkingFee = (GetNumNights() * 12.75);
    }
    ui->parkingFeeLabel->setText("$" + QString::number(parkingFee));
    double resortFee = 0;
    resortFee = GetNumNights() * 15;
    ui->resortFeeLabel->setText("$" + QString::number(resortFee));
    ui->totalDueLabel->setText("$" + QString::number(CalculateCost() + CalculateCostTax() + parkingFee + resortFee));

}

// move to the second page and check validations
void MainWindow::on_nextButton_clicked()
{
    QMessageBox warning;
    if(ui->firstNameText->toPlainText().length() == 0 || ui->lastNameText->toPlainText().length() == 0){
        warning.setIcon(warning.Warning);
        warning.setText("Please enter you first and last name.");
        warning.setWindowTitle("*Requirement");
        warning.exec();
    } else if(GetRoomType() == 0){
              warning.setIcon(warning.Warning);
              warning.setText("Please select a room.");
              warning.setWindowTitle("*Requirement");
              warning.exec();
          } else {
        ui->stackedWidget->setCurrentIndex(1);
    }


}


// switch back to page one
void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->creditCardLineEdit->clear();
}

// calculate cost of the room
double MainWindow::CalculateCost() {
    double total;
    if(GetRoomType() == 1){
        total = GetNumNights() * 284;
    } else if (GetRoomType() == 2){
        total = GetNumNights() * 325;
    } else if (GetRoomType() == 3){
        total = GetNumNights() * 290;
    } else {
        total = GetNumNights() * 350;
    }
    return total;
}

// calculate tax
double MainWindow::CalculateCostTax(){
    double totalWithTax;
    totalWithTax = CalculateCost() * 0.15;
    return totalWithTax;
}

// hold valvue day length value
void MainWindow::on_dateLengthSpinBox_valueChanged(int arg1)
{
    SetNumNights(arg1);
    ui->totalEstimateLabel->setText("$" + QString::number(CalculateCost()));
    CurrentChoice();
}

// parking condition
void MainWindow::on_parkingCheckBox_clicked(bool checked)
{
    SetParkingNeeded(checked);
    CurrentChoice();

}

// display booking confirmation
void MainWindow::on_confirmButton_clicked()
{
    QString roomType, parking, creditcard, creditNumbers, lastFourDigits;
    QString name, date,numNight,numGuest;
    QMessageBox msgBox, warning;

    if(GetRoomType() == 1){
        roomType = "Standdard 2-Queen";
    } else if (GetRoomType() == 2){
       roomType = "Atrium 2-Queen";
    } else if (GetRoomType() == 3){
        roomType = "Standard 1-King";
    } else {
        roomType = "Atrium 1-King";
    }

    if(GetParkingNeeded()){
        parking = "Parking included.";
    } else {
        parking = "Parking not included.";
    }

    if(ui->masterCardButton->isChecked() || ui->visaButton->isChecked() || ui->americanButton->isChecked() || ui->discoverButton->isChecked()){
    if(ui->masterCardButton->isChecked()){
        creditcard = "MasterCard ";
    } else if (ui->visaButton->isChecked()){
        creditcard = "VisaCard ";
    } else if (ui->americanButton->isChecked()){
        creditcard = "American Express ";
    } else if (ui->discoverButton->isChecked()){
        creditcard = "Discover ";
    }

    creditNumbers =  ui->creditCardLineEdit->text();
    lastFourDigits = creditNumbers.right(4);
    name = "Name:     " + ui->firstNameText->toPlainText() +" "+ ui->lastNameText->toPlainText() + "\n" ;
    date = "Reservation on:     " + ui->dateEdit->date().toString("MM-dd-yyyy\n") + "Days of reservation: ";
    numNight = QString::number(ui->dateLengthSpinBox->value()) + " -Night\n";
    numGuest = "Guests:  " + QString::number(ui->guestSpinBox->value()) + ", Children:  " +
               QString::number(ui->childrenSpinbox->value()) + "\n";


    QString reservation = name + date + numNight + "Room Type:     " +roomType + "\n" + parking + "\n" + numGuest + "Total Amount:     " +
            ui->totalDueLabel->text() + "\n" +"Credit card : " + creditcard + " -ending in " + lastFourDigits  + "\n" +
            "Expires on " + (ui->monthComboBox->currentText()) + "/" + (ui->yearComboBox->currentText()) + "\n\nWe do hope you enjoy your stay. \n\nMr." +
            ui->lastNameText->toPlainText();

    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setText(reservation);
    msgBox.setWindowTitle("Booking Confirmation");
    msgBox.exec();
    } else {
       warning.setText("Please select the credit card options.");
       warning.setIcon(warning.Warning);
       warning.setWindowTitle("*Requirement");
       warning.exec();
}
}

// conditions for guest limit
void MainWindow::on_guestSpinBox_valueChanged()
{
        if (roomType == 1){
        ui->guestSpinBox->setMaximum(4 - ui->childrenSpinbox->value());
        ui->childrenSpinbox->setMaximum(4 - ui->guestSpinBox->value());

    } else if (roomType == 2){
        ui->guestSpinBox->setMaximum(4 - ui->childrenSpinbox->value());
        ui->childrenSpinbox->setMaximum(4 - ui->guestSpinBox->value());

    } else if (roomType == 3){
        ui->guestSpinBox->setMaximum(3 - ui->childrenSpinbox->value());
        ui->childrenSpinbox->setMaximum(3 - ui->guestSpinBox->value());

    } else {
        ui->guestSpinBox->setMaximum(3 - ui->childrenSpinbox->value());
        ui->childrenSpinbox->setMaximum(3 - ui->guestSpinBox->value());
    }
}

// conditions for guest limit
void MainWindow::on_childrenSpinbox_valueChanged()
{
    if (roomType == 1){
    ui->guestSpinBox->setMaximum(4 - ui->childrenSpinbox->value());
    ui->childrenSpinbox->setMaximum(4 - ui->guestSpinBox->value());

} else if (roomType == 2){

    ui->guestSpinBox->setMaximum(4 - ui->childrenSpinbox->value());
    ui->childrenSpinbox->setMaximum(4 - ui->guestSpinBox->value());

} else if (roomType == 3){

    ui->guestSpinBox->setMaximum(3 - ui->childrenSpinbox->value());
    ui->childrenSpinbox->setMaximum(3 - ui->guestSpinBox->value());

} else {

    ui->guestSpinBox->setMaximum(3 - ui->childrenSpinbox->value());
    ui->childrenSpinbox->setMaximum(3 - ui->guestSpinBox->value());
}
}


void MainWindow::on_masterCardButton_clicked()
{

        ui->creditCardLineEdit->clear();
        ui->creditCardLineEdit->setMaxLength(16);
        ui->creditCardLineEdit->setInputMask("5999-9999-9999-9999;_");
        ui->creditCardLineEdit->setText("5");
}

void MainWindow::on_visaButton_clicked()
{

        ui->creditCardLineEdit->clear();
        ui->creditCardLineEdit->setMaxLength(16);
        ui->creditCardLineEdit->setInputMask("4999-9999-9999-9999;_");
        ui->creditCardLineEdit->setText("4");
}

void MainWindow::on_americanButton_clicked()
{
        ui->creditCardLineEdit->clear();
        ui->creditCardLineEdit->setMaxLength(15);
        ui->creditCardLineEdit->setInputMask("3999-999999-99999;_");
        ui->creditCardLineEdit->setText("3");
}

void MainWindow::on_discoverButton_clicked()
{
        ui->creditCardLineEdit->clear();
        ui->creditCardLineEdit->setMaxLength(16);
        ui->creditCardLineEdit->setInputMask("6999-9999-9999-9999;_");
        ui->creditCardLineEdit->setText("6");
}


string MainWindow::GetCustomerName() {
  return customerName;
}
void MainWindow::SetCustomerName(string name) {
  customerName = name;
}
int MainWindow::GetRoomType(){
  return roomType;
}
void MainWindow::SetRoomType(int type){
  roomType = type;
}
int MainWindow::GetNumNights(){
  return numNights;
}
void MainWindow::SetNumNights(int nights){
  numNights = nights;
}
bool MainWindow::GetParkingNeeded(){
  return parkingNeeded;
}
void MainWindow::SetParkingNeeded(bool needed){
  parkingNeeded = needed;
}


// load the image from source
void MainWindow::imageInput(){
    QString standardQueenBed = ":/images/standard-queenbed.jpg";
    QString standardQueenBath = ":/images/standard-queenbath.jpg";
    QString atriumQueenBed = ":/images/atirum-queenbed.jpg";
    QString atriumQueenBath = ":/images/atrium-queenbath.jpg";
    QString standardKingBed = ":/images/standard-kingbed.jpg";
    QString standardKingBath = ":/images/standard-kingbath.jpg";
    QString atriumKingBed = ":/images/atrium-kingbed.jpg";
    QString atriumKingBath = ":/images/atrium-kingbath.jpg";

    if(imageSqueen.load(standardQueenBed)){
        imageSqueen = imageSqueen.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageSqueen1.load(standardQueenBath)){
        imageSqueen1 = imageSqueen1.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageSking.load(standardKingBed)){
        imageSking = imageSking.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageSking1.load(standardKingBath)){
        imageSking1 = imageSking1.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageAqueen.load(atriumQueenBed)){
        imageAqueen = imageAqueen.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageAqueen1.load(atriumQueenBath)){
        imageAqueen1 = imageAqueen1.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageAking.load(atriumKingBed)){
        imageAking = imageAking.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageAking1.load(atriumKingBath)){
        imageAking1 = imageAking1.scaled(ui->imageLabel1->size(), Qt::KeepAspectRatioByExpanding);
    }

}

// exit the program
void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
