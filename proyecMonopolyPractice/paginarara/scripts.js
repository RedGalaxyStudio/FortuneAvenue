// Simplemente para un efecto suave al hacer clic en los enlaces de navegación
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
        e.preventDefault();
        document.querySelector(this.getAttribute('href')).scrollIntoView({
            behavior: 'smooth'
        });
    });
});


var n_estrellas = 500;
var cv, cx, estrellas = [];
var vel_max = 10;

function prepararEstrella(index) {
    estrellas[index] = {
        'color': 'rgb(' +
            (Math.random() * 255) + ',' +
            (Math.random() * 255) + ',' +
            (Math.random() * 255) + ')',
        'vel_x': (Math.random() * vel_max * 2) - vel_max + 1,
        'vel_y': (Math.random() * vel_max * 2) - vel_max + 1,
        'x': Math.random() * cv.width, // Posición inicial aleatoria
        'y': Math.random() * cv.height
    };
}

function pintar() {
    // Limpiar el área con un cuadro negro
    cx.fillStyle = '#000';
    cx.fillRect(0, 0, cv.width, cv.height);

    for (var i = 0; i < n_estrellas; i++) {
        var e = estrellas[i];
        cx.fillStyle = e.color;
        if (e.x > cv.width || e.y > cv.height || e.x < 0 || e.y < 0) {
            prepararEstrella(i); // Reposicionar estrella si sale del canvas
        }
        e.x += e.vel_x; // Actualizar posición en X
        e.y += e.vel_y; // Actualizar posición en Y
        cx.fillRect(e.x, e.y, 2, 2); // Dibujar estrella
    }

    requestAnimationFrame(pintar); // Mejor rendimiento que setTimeout
}

function ajustarCanvas() {
    cv.width = window.innerWidth; // Ancho dinámico
    cv.height = window.innerHeight; // Alto dinámico
}

window.onload = function () {
    cv = document.getElementById('lienzoo');
    cx = cv.getContext('2d');

    ajustarCanvas(); // Ajustar el canvas al cargar

    // Redimensionar el canvas cuando cambie el tamaño de la ventana
    window.addEventListener('resize', ajustarCanvas);

    // Inicializar las estrellas
    for (var i = 0; i < n_estrellas; i++) {
        prepararEstrella(i);
    }

    // Comenzar la animación
    pintar();
};


document.getElementById('toggleButton').addEventListener('click', function() {
    var barraLateral = document.getElementById('barraLateral');
    this.style.display = 'none'; // Hace que el botón desaparezca
    barraLateral.classList.toggle('open'); // Alterna la visibilidad de la barra lateral
});

document.getElementById('closeButton').addEventListener('click', function() {
    var barraLateral = document.getElementById('barraLateral');
    var toggleButton = document.getElementById('toggleButton');
  
    barraLateral.classList.remove('open'); // Cierra la barra lateral cuando se hace clic en el botón '×'
    toggleButton.style.display = 'block'; 
});

// Cerrar la barra lateral si se hace clic fuera de ella
document.addEventListener('click', function(event) {
    var barraLateral = document.getElementById('barraLateral');
    var toggleButton = document.getElementById('toggleButton');
    
    // Verifica si el clic fue fuera de la barra lateral y el botón
    if (!barraLateral.contains(event.target) && !toggleButton.contains(event.target)) {
        barraLateral.classList.remove('open');
    }
});

// Opción de cerrar la barra lateral después de un tiempo de inactividad
let timeout;
document.addEventListener('mousemove', resetTimeout);
document.addEventListener('keydown', resetTimeout);

function resetTimeout() {
    clearTimeout(timeout);
    timeout = setTimeout(function() {
        var barraLateral = document.getElementById('barraLateral');
        barraLateral.classList.remove('open'); // Cierra la barra lateral después de 5 segundos de inactividad
    }, 5000); // 5000 milisegundos (5 segundos)
}
