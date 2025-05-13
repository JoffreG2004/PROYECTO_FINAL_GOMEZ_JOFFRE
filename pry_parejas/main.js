function mostrar(id) {
  const secciones = document.querySelectorAll('.seccion');
  secciones.forEach(seccion => seccion.classList.add('d-none'));
  const seccionActiva = document.getElementById(id);
  if (seccionActiva) {
    seccionActiva.classList.remove('d-none');
  }
}