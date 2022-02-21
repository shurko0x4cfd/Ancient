
/* Alexander (Shurko) Stadnichenko */
/* Public domain */

;(function (){

var dndstuff = document.getElementById ('dndstuff');
var leftpane = document.getElementById('leftpane');

function dndinit (){
    dndstuff.addEventListener ('dragstart', dstart , false);

    leftpane.addEventListener ('dragenter', function (e){ e.preventDefault (); console.log ('Target: dnd enter'); }, false);
    leftpane.addEventListener ('dragover',  function (e){ e.preventDefault (); console.log ('Target: dnd over'); }, false);
    leftpane.addEventListener ('drop', drophandler, false); }

function dstart (e){
    console.log ('Source: drag start'); }

function drophandler (e){
    e.preventDefault ();
    leftpane.innerText = 'Done :)';
    console.log ('Target: dnd dropped'); 
}

window.addEventListener ('load', dndinit, false);

})()
