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

  let edad = 0;
  try {
    const fecha = new Date(fechaNacimiento);
    const hoy = new Date();
    edad = hoy.getFullYear() - fecha.getFullYear();
    const m = hoy.getMonth() - fecha.getMonth();
    if (m < 0 || (m === 0 && hoy.getDate() < fecha.getDate())) {
      edad--;
    }
  } catch (e) {
    Swal.fire({
      icon: 'error',
      title: 'Fecha inválida',
      text: 'La fecha de nacimiento no es válida.',
      confirmButtonColor: '#d33'
    });
    return;
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
    fechaNacimiento,
    latitud,
    longitud,
    usuario,
    contrasena,
    foto: fotoBase64
  };

  let perfiles = JSON.parse(localStorage.getItem("perfilesUsuario") || "[]");
  const usuarioExistente = perfiles.find(p => p.usuario === usuario);
  if (usuarioExistente) {
    Swal.fire({
      icon: 'error',
      title: 'Usuario existente',
      text: 'Ya existe un perfil con ese nombre de usuario. Por favor elige otro.',
      confirmButtonColor: '#d33'
    });
    return;
  }

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
