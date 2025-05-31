function guardar_datos() {
  var nombre = document.getElementById("nombre").value.trim();
  var apellido = document.getElementById("apellido").value.trim();
  var departamento = document.getElementById("departamento").value.trim();
  var fechaNacimiento = document.getElementById("edad").value;
  var latitud = document.getElementById("txt_latitud").value.trim();
  var longitud = document.getElementById("txt_longitud").value.trim();


  if (!nombre || !apellido || !departamento || !fechaNacimiento || !latitud || !longitud) {
    alert("Por favor completa todos los campos y obtén tu localización.");
    return;
  }

  var partes = fechaNacimiento.split("-");
  var año = parseInt(partes[0], 10);
  var mes = parseInt(partes[1], 10);
  var dia = parseInt(partes[2], 10);


  var hoy = new Date();
  var edad = hoy.getFullYear() - año;
  var mesActual = hoy.getMonth() + 1;
  var diaActual = hoy.getDate();
  if (mesActual < mes || (mesActual === mes && diaActual < dia)) {
    edad--;
  }


  var canvas = document.getElementById("foto");
  var fotoBase64 = canvas.toDataURL("image/png");


  var datos = {
    nombre: nombre,
    apellido: apellido,
    departamento: departamento,
    edad: edad,
    latitud: latitud,
    longitud: longitud,
    foto: fotoBase64
  };


  localStorage.setItem("datosUsuario", JSON.stringify(datos));

  console.log("Datos guardados:", datos);

  alert("Datos guardados correctamente.");
}
