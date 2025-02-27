const express = require('express');
const app = express();
const path = require('path');
const TelegramBot = require('node-telegram-bot-api');
const nodemailer = require('nodemailer')


require('dotenv').config();

const SendSubject = 'ddpolytechnic2016@gmail.com'
const PORT = 5000
const token = '1858844290:AAG4xVcUFcD6nNnKqz1biKvcGrhwNCsOHMk';
const bot = new TelegramBot(token, {polling: true});
const chatId = '-519873227';


let transporter = nodemailer.createTransport({
  service: 'gmail',
  host: 'smtp.gmail.com',
  port: 587,
  secure: false,
  auth: {
    user: process.env.SMTP_USER,
    pass: process.env.SMTP_PASSWORD,
  },
})



app.use(express.static(__dirname));

app.post('/', (req, res) => {
    let {score, author} = req.headers

    bot.sendMessage(chatId, `TR-15 Rudenko Vladislav LR4-6: \nStudent: ${author}\nScore : ${score} of 10`)

    transporter.sendMail({
        from: process.env.SMTP_USER,
        to: SendSubject,
        subject: 'Результати тестування',
        html:
          `<h1>TR-15 Руденко Владислав Лаб4-6 Web</h1>
          <h3>Виконавець: ${author}</h3>
          <h3>Результат тесту: ${score} of 10</h3>`,
    }, (error, info) => {
        if (error) {
       console.log(error);
        } else {
          console.log('Email sent: ' + info.response);
        }
    })
})

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname + '/index.html'));
})

app.listen(PORT, () => {
    console.log(`Server started on port: ${PORT}`);
})