var bgMusic = $("#background")[0],
playing = true;

bgMusic.addEventListener('ended', function () {
    this.currentTime = 0;
    if (playing) {
        this.play();
    }
}, false);

background.play();

var correct_items = new Array();
var clicked_item = $(this).attr(".yes");

$(document).ready(function () {

    $('#next-button2').hide();

    $('#game-info').modal('show');

    $('#balloon-game').hide();

    $('#next-button').click(function () {
        $('#next-button').hide();
        $('#game-info').modal('hide');
        $('#balloon-game').show();
    });

    $('#next-button2').click(function () {
        $('#next-button2').hide();
        $('#balloon-game').hide();
        $('#game-complete').modal('show');
    });

    // Quit screen function

    $('#close').click(function () {
        $('#game-close').modal('show');
    });

    $('.No-Btns').click(function () {
        $('#game-close').modal('hide');
    });

    $('#next-button3').click(function () {
        $("#putcontenthere").load("action_items/ai4.html");
    });

});

$(document).ready(function () {

    $('#ball').one("click", function () {
        $('#n-active').hide();
        $('#active').show();
        balloon.load();
        balloon.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball2').one("click", function () {
        $('#n-active2').hide();
        $('#active2').show();
        balloon2.load();
        balloon2.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball3').one("click", function () {
        $('#n-active3').hide();
        $('#active3').show();
        balloon3.load();
        balloon3.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            $('#next-button2').show();
        }
    });

    $('#ball4').one("click", function () {
        $('#n-active4').hide();
        $('#active4').show();
        balloon.load();
        balloon.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball5').one("click", function () {
        $('#n-active5').hide();
        $('#active5').show();
        balloon2.load();
        balloon2.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball6').one("click", function () {
        $('#n-active6').hide();
        $('#active6').show();
        balloon3.load();
        balloon3.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball7').one("click", function () {
        $('#n-active7').hide();
        $('#active7').show();
        balloon.load();
        balloon.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball8').one("click", function () {
        $('#n-active8').hide();
        $('#active8').show();
        balloon2.load();
        balloon2.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball9').one("click", function () {
        $('#n-active9').hide();
        $('#active9').show();
        balloon3.load();
        balloon3.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball10').one("click", function () {
        $('#n-active10').hide();
        $('#active10').show();
        balloon.load();
        balloon.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball11').one("click", function () {
        $('#n-active11').hide();
        $('#active11').show();
        balloon2.load();
        balloon2.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball12').one("click", function () {
        $('#n-active12').hide();
        $('#active12').show();
        balloon3.load();
        balloon3.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball13').one("click", function () {
        $('#n-active13').hide();
        $('#active13').show();
        balloon.load();
        balloon.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball14').one("click", function () {
        $('#n-active14').hide();
        $('#active14').show();
        balloon2.load();
        balloon2.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

    $('#ball15').one("click", function () {
        $('#n-active15').hide();
        $('#active15').show();
        balloon3.load();
        balloon3.play();

        correct_items.push(clicked_item);

        if (correct_items.length === 1) {

        } else if (correct_items.length === 15) {
            yeah.load();
            yeah.play();
            $('#next-button2').show();
        }
    });

});