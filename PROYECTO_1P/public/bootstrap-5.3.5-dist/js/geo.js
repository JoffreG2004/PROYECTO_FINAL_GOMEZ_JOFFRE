let my_geolocation = navigator.geolocation;

if(my_geolocation){
    my_geolocation.getCurrentPosition(function(posicion){
console.log(posicion.coords.latitude)

document.getElementById("txt_latitud").value=posicion.coords.latitude;
document.getElementById("txt_longitud").value=posicion.coords.longitude;

var map = L.map('map').setView([posicion.coords.latitude, posicion.coords.longitude], 15);

L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

    })
}else{
    alert('navegador no soporta cambia el pc.')
}