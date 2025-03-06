#include "MailManager.h"

SMTPData smtpData;

void sendEmail(int imageQuantity)
{
  smtpData.setLogin(smtpServer, smtpServerPort, senderEmail, senderPassword);
  smtpData.setSubject(emailSubject);
  smtpData.setSender("ESP32-CAM", senderEmail);
  smtpData.setMessage("Movement Detected from ESP-32 CAM", false);
  smtpData.addRecipient(emailRecipient);
  smtpData.setFileStorageType(MailClientStorageType::SPIFFS);
  smtpData.setPriority(HIGH);
  smtpData.setSendCallback(resCallback);
  // SET IMAGE ATTACHMENT
  for (int i = 0; i < imageQuantity; i++)
  {
    smtpData.addAttachFile("/" + String(i) + ".jpg", "image/jpg");
  }

  if (!MailClient.sendMail(smtpData))
    Serial.println(MailClient.smtpErrorReason());

  smtpData.empty();
}

void resCallback(SendStatus msg)
{
  Serial.println(msg.info());
}
