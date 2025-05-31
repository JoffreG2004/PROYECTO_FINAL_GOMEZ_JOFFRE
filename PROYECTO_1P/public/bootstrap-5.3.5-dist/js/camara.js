let contenido_camara = null;

navigator.mediaDevices.getUserMedia({ video: true })
.then(res => {
    contenido_camara = res;
    document.getElementById("my_video").srcObject = contenido_camara;
})
.catch(error => {
    console.error("Error al acceder a la cámara:", error);
});

function fnc_TomarFoto() {
    const my_video = document.getElementById("my_video");
    const my_foto = document.getElementById("foto");
    const ctx = my_foto.getContext("2d");
    // Ajustar tamaño del canvas a video
    my_foto.width = my_video.videoWidth;
    my_foto.height = my_video.videoHeight;
    ctx.drawImage(my_video, 0, 0, my_foto.width, my_foto.height);
}

