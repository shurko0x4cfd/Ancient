
/* Alexander (Shurko) Stadnichenko */
/* Public domain */

;(function(){

cl = console.log

var tinside = document.getElementsByClassName ("textinside")[0] ;
tinside.style.left = "10px";
tinside.style.top = "10px";

var area = document.getElementsByClassName ("panarea")[0] ;
tinside.style.width  = area.getClientRects ()[0].width  - 40 + "px";
tinside.style.height = area.getClientRects ()[0].height - 40 + "px";

var body = document.getElementsByTagName ("body")[0] ;

startpoint = {"x": 0, "y": 0};
startlocation = {"x": 0, "y": 0};

in_moving = false;

var shift_div = function (dx, dy) {
    tinside.style.left = startlocation.x + dx + "px";
    tinside.style.top  = startlocation.y + dy + "px";
}

var mmove = function (e) {
    if (in_moving === false) { return }

    e.preventDefault ();

    dx = e.clientX - startpoint.x;
    dy = e.clientY - startpoint.y;

    shift_div (dx, dy); }

var mdown = function (e) {
    e.preventDefault ();

    startpoint.x = e.clientX;
    startpoint.y = e.clientY;

    startlocation.x = parseInt (tinside.style.left);
    startlocation.y = parseInt (tinside.style.top);

    body.style.cursor = "move";

    in_moving = true;

    area.removeEventListener("mousedown", mdown);
    body.addEventListener ("mouseup", mup, false);
    body.addEventListener ("mousemove", mmove, false);}

var mup = function (e) {
    e.preventDefault ();

    body.style.cursor = "default";
    in_moving = false;

    body.removeEventListener("mouseup", mup);
    body.removeEventListener("mousemove", mmove);
    area.addEventListener ("mousedown", mdown, false); }


area.addEventListener ("mousedown", mdown, false);

})();




