$(document).ready(function() {
    // Sprawdzenie, czy użytkownik jest zalogowany, i zaktualizowanie interfejsu
    updateLoginStatus();

    // Obsługa formularza logowania
    $("#loginForm").submit(function(event) {
        event.preventDefault(); // Zapobieganie domyślnemu zachowaniu formularza

        // Pobieranie danych użytkownika
        const username = $("#nick").val();
        // Zapisywanie nazwy użytkownika do localStorage
        localStorage.setItem("username", username);

        // Przekierowanie użytkownika do strony, z której przyszedł
        const lastPage = localStorage.getItem("lastPage") || 'index.html'; // 'index.html' to domyślna strona startowa
        window.location.href = lastPage;
    });

    // Wylogowanie użytkownika
    $("#login").click(function() {
        if ($(this).text() === "Log out") {
            // Usuwanie danych użytkownika z localStorage
            localStorage.removeItem("username");

            // Aktualizacja interfejsu
            updateLoginStatus();
        } else {
            // Zapisanie obecnej strony, aby można było na nią wrócić
            localStorage.setItem("lastPage", window.location.href);

            // Przekierowanie do strony logowania
            window.location.href = 'login.html';
        }
    });
});

// Funkcja aktualizująca stan interfejsu użytkownika
function updateLoginStatus() {
    const username = localStorage.getItem("username");
    if (username) {
        // Zmiana przycisku na 'Log out' i wyświetlenie powitania
        $("#login").text("Log out");
        $("#login_text").text("Hello " + username);
        $("#login_text").css("color", "#fff");
        $("#login_text").css("font-weight", "bold");
        $("#login_text").css("font-size", "16px");
        $("#login_text").css("width", "120px");
        $("#login_text").css("text-align", "center");
    } else {
        // Zmiana przycisku na 'Sign in' i usunięcie powitania
        $("#login").text("Sign in");
        $("#login_text").text("");
    }
}

