// Simplemente para un efecto suave al hacer clic en los enlaces de navegación
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
        e.preventDefault();
        document.querySelector(this.getAttribute('href')).scrollIntoView({
            behavior: 'smooth'
        });
    });
});
document.getElementById('toggleButton').addEventListener('click', function() {
    var barraLateral = document.getElementById('barraLateral');
    barraLateral.classList.toggle('open'); // Alterna la visibilidad de la barra lateral
});

document.getElementById('closeButton').addEventListener('click', function() {
    var barraLateral = document.getElementById('barraLateral');
    barraLateral.classList.remove('open'); // Cierra la barra lateral cuando se hace clic en el botón '×'
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
