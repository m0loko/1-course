document.getElementById("submitButton").addEventListener("click", function () {
    const name = document.getElementById("name").value;
    const surname = document.getElementById("surname").value;
    const secname = document.getElementById("secname").value;
    const email = document.getElementById("email").value;
    const phone = document.getElementById("phone").value;
    const faculty = document.getElementById("faculty").value;
    const group = document.getElementById("group").value;
    const course = document.getElementById("course").value;

    const selectedSocials = Array.from(
        document.querySelectorAll(".checkboxes input:checked")
    ).map(input => input.value);

    const footer = document.getElementById("output");
    footer.innerHTML = `
        <p><strong>Имя:</strong> ${name}</p>
        <p><strong>Отчество:</strong> ${surname}</p>
        <p><strong>Фамилия:</strong> ${secname}</p>
        <p><strong>Email:</strong> ${email}</p>
        <p><strong>Телефон:</strong> ${phone}</p>
        <p><strong>Факультет:</strong> ${faculty}</p>
        <p><strong>Группа:</strong> ${group}</p>
        <p><strong>Курс:</strong> ${course}</p>
        <p><strong>Соцсети:</strong> ${selectedSocials.join(", ")}</p>
    `;
});
