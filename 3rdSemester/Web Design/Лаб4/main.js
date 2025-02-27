let pibInput = document.getElementById('pibInput');
let testButton = document.getElementById('testButton');
let finishButton = document.getElementById('finishButton');
let main = document.getElementsByClassName('main');
let finish = document.getElementsByClassName('finish')
let form1 = document.getElementsByClassName('form');

class Coristuvach 
{
    constructor(surname, firstname)
    {
        this.surname = surname;
        this.firstname = firstname;
    }
}

class Student extends Coristuvach {
    constructor(group, surname, firstname, result) {
        super(surname, firstname);
        this.group = group;
        this.result = result;
    }
    ShowData()
    {
        console.log(Student);
    }
}
class success extends Student
{
    Bal()
    {
        this.result=score/numberofiteration;
        return result;
    }
    ShowData()
    {
        super.ShowData();
        console.log(Bal());
    }
    
}

function insertBefore(newNode, existingNode) {
    existingNode.parentNode.insertBefore(newNode, existingNode);
}

/* зміна порядоку в масиві */
const shuffle = (arr) => {

    let currentIndex = arr.length, temporaryValue, randomIndex;

    while(0 !== currentIndex) {
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -=1;

        temporaryValue = arr[currentIndex];
        arr[currentIndex] = arr[randomIndex];
        arr[randomIndex] = temporaryValue;
    }


    return arr;
}

let questions = [
    {
        question: 'Який тег позначає силку в html',
        type: 'select',
        answers: ['a', 'b', 'p', 'i'],
        correctAnswers: ['a']
    },
    {
        question: 'Як зробити коментар в html?(<> нехтуйте дужками)',
        type: 'radio',
        answers: ['!-- --', '* *', '/ /', '/* */'],
        correctAnswers: ['!-- --']
    },
    {
        question: 'Як називається html тег де знаходиться основна розмітка?',
        type: 'radio',
        answers: ['html', 'head', 'body', 'main'],
        correctAnswers: ['body']
    },
    {
        question: 'Які з поданих є inline тегами?',
        type: 'checkbox',
        answers: ['span', 'div', 'b', 'ul'],
        correctAnswers: ['span', 'b']
    },
    {
        question: "Як створити область для вводу користувачем ВЕЛИКОЇ кількості тексту?",
        type: 'radio',
        answers: ['input', 'p', 'textarea', 'block'],
        correctAnswers: ['textarea']
    },
    {
        question: 'Який заголовок буде найбільшим із поданих?',
        type: 'select',
        answers: ['h1', 'h2', 'h3', 'h4'],
        correctAnswers: ['h1']
    },
    {
        question: "HTML - що це?",
        type: 'radio',
        answers: ['мова програмування', 'набір символів', 'мова для стилізації', 'мова розмітки'],
        correctAnswers: ['мова розмітки']
    },
    {
        question: 'Введіть тег для переносу на наступний рядок',
        type: 'input',
        answers: [],
        correctAnswers: ['br']
    },
    {
        question: 'Який тег використовується для написання підвалу сайту?',
        type: 'input',
        answers: [],
        correctAnswers: ["footer"]
    },
    {
        question: 'Для чого потрібен тег head?',
        type: 'radio',
        answers: ['для відображення шапки сайту', 'для підключення файлів і налаштування сторінки', 'потрібний для присвоєння аргументів', 'для основної розмітки'],
        correctAnswers: ['для підключення файлів і налаштування сторінки']
    },
];


let questionNum = 1;
/* Нові діти! */
questions.map(el => {
    let shuffledAnswers = shuffle(el.answers);
    const child = document.createElement('form');
    child.className = 'test_item';
    child.id = questionNum;

    switch(el.type) {
        case 'checkbox':
            child.innerHTML = `
            <div class="test_title">${el.question}</div>
            <div class="variantes">
                <div class="variant">
                    <input id="var1" name="${el.question}" value="${shuffledAnswers[0]}" type="checkbox" />
                    <label for="${el.question}">${shuffledAnswers[0]}</label>
                </div>
                <div class="variant">
                    <input id="var2" name="${el.question}" value="${shuffledAnswers[1]}" type="checkbox" />
                    <label for="${el.question}">${shuffledAnswers[1]}</label>
                </div>
                <div class="variant">
                    <input id="var3" name="${el.question}" value="${shuffledAnswers[2]}" type="checkbox" />
                    <label for="${el.question}">${shuffledAnswers[2]}</label>
                </div>
                <div class="variant">
                    <input id="var4" name="${el.question}" value="${shuffledAnswers[3]}" type="checkbox" />
                    <label for="${el.question}">${shuffledAnswers[3]}</label>
                </div>
            </div>`
            break;
        case 'select':
            child.innerHTML = `
            <div class="test_title">${el.question}</div>
                <select class="testSelect" name="${el.question}">
                    <option value="${shuffledAnswers[0]}">${shuffledAnswers[0]}</option>
                    <option value="${shuffledAnswers[1]}">${shuffledAnswers[1]}</option>
                    <option value="${shuffledAnswers[2]}">${shuffledAnswers[2]}</option>
                    <option value="${shuffledAnswers[3]}">${shuffledAnswers[3]}</option>
                </select>
            </div>`
            break;
        case 'radio':
            child.innerHTML = `
            <div class="test_title">${el.question}</div>
            <div class="variantes">
                <div class="variant">
                    <input type="radio" id="contact1" name="${el.question}" value="${shuffledAnswers[0]}" />
                    <label for="${el.question}">${shuffledAnswers[0]}</label>
                </div>
                <div class="variant">
                    <input type="radio" id="contact2" name="${el.question}" value="${shuffledAnswers[1]}" />
                    <label for="${el.question}">${shuffledAnswers[1]}</label>
                </div>
                <div class="variant">
                    <input type="radio" id="contact3" name="${el.question}" value="${shuffledAnswers[2]}" />
                    <label for="${el.question}">${shuffledAnswers[2]}</label>
                </div>
                <div class="variant">
                    <input type="radio" id="contact4" name="${el.question}" value="${shuffledAnswers[3]}" />
                    <label for="${el.question}">${shuffledAnswers[3]}</label>
                </div>
            </div>`
            break;
        case 'input':
            child.innerHTML = `
            <div class="test_title">${el.question}</div>
            <input class="testInput" type="text" name="${el.question}" required />
            `
            break;
    }

    insertBefore(child, form1[0].firstElementChild)
    questionNum++;
})

/* Кнопка */
testButton.addEventListener('click', (e) => {
    e.preventDefault();

    let results = [];
    let testScore = 0;

    questions.map((el, index) => {
        let form = document.getElementById(`${index + 1}`);
        let data = new FormData(form);

        results.push({
            question: el.question,
            answers: []
        })

        for(let [question, answer] of data) {
            results[index].answers.push(answer);
        }
    })

    for(let i = 0; i < results.length; i++) {
        if(JSON.stringify(questions[i].correctAnswers.sort()) === JSON.stringify(results[i].answers.sort()))
            testScore += 1;
    }

    let pib = pibInput.value;
    let pibArr = pib.split(' ');

    let student = new Student(pibArr[0], pibArr[1], pibArr[2], testScore)

    var pibHTML = document.getElementsByClassName('pibHTML');
    var resHTML = document.getElementsByClassName('resHTML');
    pibHTML[0].innerHTML = `${student.group} ${student.surname} ${student.firstname}`
    resHTML[0].innerHTML = `${student.result}/10`;

    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/");
    xhr.setRequestHeader('score', student.result);
    xhr.setRequestHeader('author', `${student.group} ${student.surname} ${student.firstname}`);
    xhr.send();

    main[0].style.display = 'none';
    finish[0].style.display = 'flex';
})

/* Кнопка Назад */
finishButton.addEventListener('click', () => {
    location.reload();
})