const img1 = document.getElementById("image1");
const img2 = document.getElementById("image2")
const img3 = document.getElementById("image3")

img1.addEventListener("mouseover", function () {
    img1.style.display = "none";
    const someText = document.createElement("p");
    someText.innerText =
    "На изображении Санта-Клаус. Он носит традиционный красный костюм с белой меховой отделкой, шапку, белую бороду и круглые очки.";
    document.getElementById("one").appendChild(someText);
    someText.style.display = "block";
});
img1.addEventListener("mouseleave", function () {
    img1.style.display = "block"; 
    const description = document.getElementById("one").querySelector("p");
    if (description) {
        description.remove(); 
    }
});


img2.addEventListener("click", function(){
	img2.style.outline = "10px solid red";

})


img3.addEventListener("mouseover", function(){
    img3.src = "./img/1.jpg"
})

img3.addEventListener("mouseout", function(){
    img3.src = "./img/3.jpg"
})