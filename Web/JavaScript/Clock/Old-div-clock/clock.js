
/* Alexander (Shurko) Stadnichenko */
/* Public domain */

;(function(){

var secarr = document.getElementsByClassName ("secarrow")[0] ;
var minarch = document.getElementsByClassName ("minarchrow")[0] ;
var ha = document.getElementsByClassName ("hourrow")[0] ;
var clocenter = document.getElementsByClassName ("clocenter")[0] ;

var secArrReposition = function (){
    var newdate = new Date;
    var mins = newdate.getMinutes ();
    var secarrangle = newdate.getSeconds () *6 -90;
    var minarchrowangle = mins *6 -90;
    var haa = newdate.getHours () %12 *30 + mins/2  -90;

    secarr.style.transform  = 'rotate(' + secarrangle + 'deg)' ;
    minarch.style.transform = 'rotate(' + minarchrowangle + 'deg)' ;
    ha.style.transform      = 'rotate(' + haa + 'deg)' ;
    clocenter.style.transform = 'rotate(0deg)' ; /* for top placing */ }

var sar_interval = setInterval(secArrReposition, 1000);

secArrReposition ();

secarr.style.visibility = 'visible';
minarch.style.visibility = 'visible';
ha.style.visibility = 'visible';
clocenter.style.visibility = 'visible';

})();


