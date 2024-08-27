var wkArray = ['Monday'
                'Tuesday'
                'Wednesday'
                'Thursday'
                'Friday'
                'Saturday'
                'Sunday'

]

for (var day in wkArray)
    {
        console.log(day)
    }
will print keys = 0, 1, 2, 3, 4, 5, 6


for (var day of wkArray)
    {
        console.log(day)
    }
will print key value = Monday, Tuesday...



Concetenate - Join multiple informations
console.log(wkArray[day] + ' is day number ' + (parseInt(day) + 1) + ' of the week!');

array functions - search this
array.size()
array.pop()
array.push()
array.shift()


map() applys a function to all elements of an array

var nums = [1, 2, 3, 4, 5];

nums = nums.map(function(num)
{
    return num * 2;
});




EVENTS = a response to a users input
event handlers are callback functions that respond to html events

<html>
    <head>
        <title>
            Event Handlers
        </title>
    </head>
    <body>
        <button onclick="">Button 1</button>
        <button onclick="">Button 2</button>
    </body>
</html>




To tell us which button was clicked, use an event handler in JS

<html>
    <head>
        <title>
            Event Handlers
        </title>
    </head>
    <body>
        <button onclick="alertName(event)">Button 1</button>
        <button onclick="alertName(event)">Button 2</button>
    </body>
</html>

JS function to interpret the alertName(event)

function alertName(event)
{
    var trigger = event.srcElement;
    alert('You clicked on ' + trigger.innerHTML); /*inner html refers to button 1 or button 2*/
}


var nameNode = document.getElementById("name");
nameNode.addEventListener("Click", function () {
    alert("Welcome to Deliberate think")
});



