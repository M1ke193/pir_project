#ifndef MAIL_MANAGER_H
#define MAIL_MANAGER_H

#include "ESP32_MailClient.h"

#define senderEmail ""
#define senderPassword ""
#define smtpServer "smtp.gmail.com"
#define smtpServerPort 465
#define emailSubject "yoo there is someone in your house :("
#define emailRecipient ""

void sendEmail(int imageQuantity);
void resCallback(SendStatus msg);

#endif 

