$(document).ready(function () {

    $('.close-Btn').click(function () {
        $('#quit-game').modal('show');
    });

    $('.no').click(function () {
        $('#quit-game').modal('hide');
    });

    $('.Next-2').click(function (){
        $("#putcontenthere").load("action_items/ai4.html");
    });
    
});