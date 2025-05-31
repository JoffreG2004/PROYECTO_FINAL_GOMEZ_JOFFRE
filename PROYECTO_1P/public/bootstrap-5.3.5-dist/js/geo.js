function registrarUbicacion() {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(
      pos => {
        document.getElementById("txt_latitud").value = pos.coords.latitude;
        document.getElementById("txt_longitud").value = pos.coords.longitude;
        document.getElementById("ubicacionConfirmada").classList.remove("d-none");
      },
      () => {
        Swal.fire({
          icon: 'error',
          title: 'Error de ubicación',
          text: 'No se pudo obtener la ubicación actual.',
          confirmButtonColor: '#dc3545'
        });
      }
    );
  } else {
    Swal.fire({
      icon: 'warning',
      title: 'No compatible',
      text: 'Tu navegador no admite geolocalización.',
      confirmButtonColor: '#ffc107'
    });
  }
}