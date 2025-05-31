function guardar_datos() {
  const nombre = document.getElementById("nombre")?.value.trim();
  const apellido = document.getElementById("apellido")?.value.trim();
  const correo = document.getElementById("correo")?.value.trim();
  const departamento = document.getElementById("departamento")?.value.trim();
  const tipoAcceso = document.getElementById("tipoAcceso")?.value.trim();
  const fechaNacimiento = document.getElementById("edad")?.value;
  const latitud = document.getElementById("txt_latitud")?.value.trim();
  const longitud = document.getElementById("txt_longitud")?.value.trim();
  const usuario = document.getElementById("usuario")?.value.trim();
  const contrasena = document.getElementById("contrasena")?.value.trim();
  const canvas = document.getElementById("foto");

  if (!nombre || !apellido || !correo || !departamento || !tipoAcceso || !fechaNacimiento || !latitud || !longitud || !usuario || !contrasena) {
    Swal.fire({
      icon: 'warning',
      title: 'Faltan campos',
      text: 'Por favor completa todos los campos antes de guardar.',
      confirmButtonColor: '#198754'
    });
    return;
  }

  const partes = fechaNacimiento.split("-");
  const año = parseInt(partes[0], 10);
  const mes = parseInt(partes[1], 10);
  const dia = parseInt(partes[2], 10);

  const hoy = new Date();
  let edad = hoy.getFullYear() - año;
  if ((hoy.getMonth() + 1) < mes || ((hoy.getMonth() + 1) === mes && hoy.getDate() < dia)) {
    edad--;
  }

  let fotoBase64 = "";
  try {
    if (canvas && canvas.width > 0 && canvas.height > 0) {
      fotoBase64 = canvas.toDataURL("image/png");
    }
  } catch (e) {
    console.warn("No se pudo obtener la imagen del canvas:", e);
  }

  const nuevoPerfil = {
    nombre,
    apellido,
    correo,
    departamento,
    tipoAcceso,
    edad,
    latitud,
    longitud,
    usuario,
    contrasena,
    foto: fotoBase64
  };

  let perfiles = JSON.parse(localStorage.getItem("perfilesUsuario") || "[]");
  perfiles.push(nuevoPerfil);
  localStorage.setItem("perfilesUsuario", JSON.stringify(perfiles));

  Swal.fire({
    icon: 'success',
    title: 'Perfil guardado',
    text: '✅ Perfil registrado correctamente.',
    confirmButtonColor: '#198754'
  });

  console.log("Todos los perfiles:", perfiles);
}
