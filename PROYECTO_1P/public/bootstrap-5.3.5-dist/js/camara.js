let contenido_camara = null;

function accederCamara() {
  const video = document.getElementById("my_video");
  const contenedor = document.getElementById("video-container");
  const errorMsg = document.getElementById("errorCamara");

  navigator.mediaDevices.getUserMedia({ video: true })
    .then(res => {
      contenido_camara = res;
      video.srcObject = contenido_camara;
      contenedor.style.display = 'block';
    })
    .catch(error => {
      console.error("Error al acceder a la cámara:", error);
      errorMsg.classList.remove("d-none");
      contenedor.style.display = 'none';
    });
}

function fnc_TomarFoto() {
  const video = document.getElementById("my_video");
  const foto = document.getElementById("foto");
  const ctx = foto.getContext("2d");
  foto.width = video.videoWidth;
  foto.height = video.videoHeight;
  ctx.drawImage(video, 0, 0, foto.width, foto.height);
  foto.classList.remove("d-none"); // Mostrar la imagen capturada
}
