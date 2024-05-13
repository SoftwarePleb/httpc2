//prevent double clicking highlighting the buttons
jQuery(".btn").mousedown(function(e){ e.preventDefault(); });

// Initialize variables.
var level = 1;
var pattern = [];
var index = 0;

// Start game
start();

// check that the pattern is correct.
$(".btn").on("click", function(event){
  console.log(event.currentTarget.classList);
  // If wrong square.
  if(pattern[index]!==event.currentTarget.classList[1]){
    end();
    start();
    // If we successfully complete the level
  } else if(index==pattern.length-1){
    flashSquare(pattern[index]);
    level++;
    $("#level-title").text("level " + level);
    var nextSquare = chooseSquare();
    setTimeout(function(){
      flashSquare(nextSquare);
      pattern.push(nextSquare);
      index = 0;
    }, 500);
  } else{
    flashSquare(pattern[index]);
    index++;
  }
})

// Press any key to start
function start(){
  $(document).on("keydown", function() {
    pattern = [];
    index = 0;
    level = 1;
    $("#level-title").text("level 1");
    $(document).off("keydown");
    firstSquare = chooseSquare();
    pattern.push(firstSquare);
    setTimeout(function () {
      flashSquare(pattern[0]);
    }, 500);
  })
}

function end(){
  $("body").addClass("game-over");
  var audio = new Audio('sounds/wrong.mp3');
  audio.play();
  setTimeout(function() {
    $("body").removeClass("game-over");
  }, 100);
  $("#level-title").text("Game Over, Press Any Key to Restart")
}

/*
Randomly generate next square
0 is green
1 is red
2 is yellow
3 is blue
*/
function chooseSquare() {
  switch (Math.floor(Math.random() * 4)) {
    case 0:
      return "green";
      break;
    case 1:
      return "red";
      break;
    case 2:
      return "yellow";
      break;
    case 3:
      return "blue";
      break;
    default:
      console.log("Random number invalid");
  }

}

/*
Flash a given square.
*/
function flashSquare(square) {
  var audio = new Audio("sounds/" + square + ".mp3");
  audio.play();
  $(".btn." + square).addClass("pressed");
  setTimeout(function() {
    $(".btn." + square).removeClass("pressed");
  }, 250);
}

// // Add the next square to the method.
// var pattern = []
// var currentSquare = chooseSquare();
// pattern.push(currentSquare);
// flashSquare(currentSquare);
