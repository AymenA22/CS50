let d = new Date();
document.body.innerHTML = "<h1>Today's date is " + d + "</h1>";


let body = document.querySelector('body');
document.querySelector('#red').addEventListener('click', function() {
    body.style.backgroundColor = 'red';
});
