var editor = ace.edit("editor");
editor.setTheme("ace/theme/monokai");
editor.session.setMode("ace/mode/c_cpp");
editor.setOptions({
    fontSize: "16px"
});



document.getElementById('compileButton').addEventListener('click', function(event) {
    event.preventDefault(); // Prevent the default form submission
    compileCode();
});

function compileCode() {
    const code = editor.getValue();
    fetch('http://localhost:5000/compile', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ code: code })
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => {
        if (data.assembly) {
            // If compilation was successful and assembly code is returned
            document.getElementById("output").value = data.assembly;
        } else if (data.error) {
            // If there's a compilation error
            document.getElementById("output").value = "Compilation Error:\n" + data.error;
        }
    })
    .catch(error => {
        console.error('Error:', error);
        document.getElementById("output").value = "Failed to compile. See console for more details.";
    });
}
