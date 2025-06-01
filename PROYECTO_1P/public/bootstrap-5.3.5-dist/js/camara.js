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
  foto.classList.remove("d-none"); 
}

document.addEventListener("DOMContentLoaded", () => {
  const inputArchivo = document.getElementById("archivoFoto");
  const canvas = document.getElementById("foto");
  const ctx = canvas.getContext("2d");
  const errorMsg = document.getElementById("errorCamara");

  inputArchivo.addEventListener("change", function(event) {
    const archivo = event.target.files[0];
    if (!archivo) return;

    const lector = new FileReader();
    lector.onload = function(e) {
      const img = new Image();
      img.onload = function() {
        canvas.width = img.width;
        canvas.height = img.height;
        ctx.drawImage(img, 0, 0, img.width, img.height);
        canvas.classList.remove("d-none");
        errorMsg.classList.add("d-none");
      };
      img.src = e.target.result;
    };
    lector.readAsDataURL(archivo);
  });
});
