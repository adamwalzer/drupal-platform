﻿$(document).ready(function () {
    
    setTimeout(function () { $('.hover-box .img-hover').height($('.sidebar .img-box img').height() * 1.065); }, 500);
    setTimeout(function () {
        $('#title1').get(0).currentTime = 0;
        $('#title1').get(0).play();
    }, 500);
    setTimeout(function () {
        $('#title2').get(0).currentTime = 0;
        $('#title2').get(0).play();
    }, 2500);
    setTimeout(function () {
        $('#title3').get(0).currentTime = 0;
        $('#title3').get(0).play();
    }, 4500);
    setTimeout(function () {
        $('#title4').get(0).currentTime = 0;
        $('#title4').get(0).play();
    }, 5500);
    $('.btn-click, .next, .prev').click(function () {
        $('#btnClick').currentTime = 0;
        $('#btnClick').get(0).play();
    });
    
    $('#home .play').click(function () {
        $('#game').get(0).play();
        $('#home').fadeOut(200);
        $('#noseWords').fadeIn(200);
        $('#title').get(0).pause();

        $('.shnose li').each(function (i) {
            var row = $(this);
            setTimeout(function () {
                row.addClass('flip');
                setTimeout(function () {
                    row.removeClass('flip');
                }, 400);
            }, 400 * i);
        });
       
    });
    $('#noseWords .card').click(function () {
        $(this).addClass('flipped');
        $('#cardFlip').get(0).currentTime = 0;
        $('#cardFlip').get(0).play();
        if ($('#Draining > .card').hasClass('flipped') && $('#Destroing > .card').hasClass('flipped') && $('#Hunting > .card').hasClass('flipped')) {
            setTimeout(function () { $('#noseWords .next').fadeIn(500); }, 1000);
        };
        
    });
    $('#noseWords .next').click(function () {
        $('#game').get(0).play();
        $('#noseWords').fadeOut(500);
        $('#upToUs').fadeIn(500);
        $('#upToUs a.next').fadeIn(500);
    });
    $('#upToUs .next').click(function () {
        $('#upToUs').fadeOut(500);
        $('#startGame').fadeIn(500);
    });

    $('#startGame .yes-btn a').click(function () {
        $('#startGame').fadeOut(500);
        $('#knowledge').fadeIn(500);
        $('#knowledge a.next').fadeIn(500);
        $('.bkg-image').css('background-image', 'url(content/_assets/Background/BKG_3.png)');
        $('.bkg-image').css('background-size', '104%');
        // $('#sort').fadeIn(500);
        // $('#sort a.next').fadeIn(500);
    });
    // $('#sort a.next').click(function () {
    //     $('#sort').fadeOut(500);
    //     $('#definitely').fadeIn(500);
    //     $('#definitely a.next').fadeIn(500);
    //     $('#slide8').get(0).currentTime = 0;
    //     $('#slide8').get(0).play();
    // });
    // $('#definitely a.next').click(function () {
    //     $('#definitely').fadeOut(500);
    //     $('#recycle').fadeIn(500);
    //     $('#recycle a.next').fadeIn(500);
    //     $('#slide9').get(0).currentTime = 0;
    //     $('#slide9').get(0).play();
    // });
    // $('#recycle a.next').click(function () {
    //     $('#recycle').fadeOut(500);
    //     $('#compost').fadeIn(500);
    //     $('#compost a.next').fadeIn(500);
    //     $('#slide10').get(0).currentTime = 0;
    //     $('#slide10').get(0).play();
    // });
    // $('#compost a.next').click(function () {
    //     $('#compost').fadeOut(500);
    //     $('#donate').fadeIn(500);
    //     $('#donate a.next').fadeIn(500);
    //     $('#slide11').get(0).currentTime = 0;
    //     $('#slide11').get(0).play();
    // });
    // $('#donate a.next').click(function () {
    //     $('#donate').fadeOut(500);
    //     $('#choseTime').fadeIn(500);
    //     $('#choseTime a.next').fadeIn(500);
    // });
    // $('.remind-time label span').click(function () {
    //     $('#checkbox').get(0).currentTime = 0;
    //     $('#checkbox').get(0).play();
    // });
    // $('#choseTime a.next').click(function () {
    //     $('#choseTime').fadeOut(500);
    //     $('#reminder1').fadeIn(500);
    //     $('#reminder1 a.next').fadeIn(500);
    // });
    // $('#reminder1 a.next').click(function () {
    //     $('#reminder1').fadeOut(500);
    //     $('#reminder2').fadeIn(500);
    //     $('#reminder2 a.next').fadeIn(500);
    // });
    // $('#reminder2 a.next').click(function () {
    //     $('#reminder2').fadeOut(500);
    //     $('#reminder3').fadeIn(500);
    //     $('#reminder3 a.next').fadeIn(500);
    // });

    // $('#reminder3 a.next').click(function () {
    //     $('#reminder3').fadeOut(500);
    //     $('#knowledge').fadeIn(500);
    //     $('#knowledge a.next').fadeIn(500);
    //     $('.bkg-image').css('background-image', 'url(content/_assets/Background/BKG_3.png)');
    //     $('.bkg-image').css('background-size', '104%');
    // });
    $('#knowledge a.next').click(function () {
        $('#knowledge').fadeOut(500);
        $('#notebook').fadeIn(500);
        $('#notebook a.next').fadeIn(500);
    });
    $('.hint-btn').click(function () {
        $('.hint-popup').fadeIn(500);
        $('#hint').get(0).currentTime = 0;
        $('#hint').get(0).play();
    });
    $('.yougotit').click(function () {
        $('.hint-popup, .hint-popup2').fadeOut(500);
    });
    $('#notebook a.next').fadeIn(500);
    $('#notebook a.next').click(function () {
        console.log($('#notebook span.emphasis').text());
       if ($('#notebook span.emphasis').text() <= 0) {
            $('#notebook').fadeOut(500);
            $('#betterway').fadeIn(500);
            $('#betterway a.next').fadeIn(500);
            // $('#howcouldyou').fadeIn(500);
            // $('#howcouldyou a.next').fadeIn(500);
            $('#game').get(0).pause();
            $('#slide17-18').get(0).currentTime = 0;
            $('#slide17-18').get(0).play();
        }
        else {
           $('#notebook .hint-popup2').fadeIn(500);
        }
    });
    // $('#howcouldyou a.next').click(function () {
    //     $('#howcouldyou').fadeOut(500);
    //     $('#betterway').fadeIn(500);
    //     $('#betterway a.next').fadeIn(500);
    //     $('#slide17-18').get(0).currentTime = 0;
    //     $('#slide17-18').get(0).play();
    // });
    $('#betterway a.next').click(function () {
        $('#betterway').fadeOut(500);
        $('#letslook').fadeIn(500);
        $('#letslook a.next').fadeIn(500);
        $('#slide19').get(0).currentTime = 0;
        $('#slide19').get(0).play();
    });
    $('#letslook a.next').click(function () {
        $('#letslook').fadeOut(500);
        $('#sort').fadeIn(500);
        $('#sort a.next').fadeIn(500);
        // $('#Listbreak1').fadeIn(500);
        // $('#Listbreak1 a.next').fadeIn(500);
        $('#game').get(0).currentTime = 0;
        $('#game').get(0).play();
        /*slider*/
        /*---------------------------------------------------*/
        /*---------------------------------------------------*/
        /*---------------------------------------------------*/

        setTimeout(function () {
            
            $('#step .slider .slide').hide();

            $('#step .slider .slide').first().show();
            $('#step .slider .slide').first().addClass('openslide');
            var num = $('#step .slider .slide').first().index() + 1;

            $(document).delegate('.sorter .sorts a', 'click', function () {
                console.log($(this).attr('id'));
                console.log($('.openslide').text());
                //$('#game').get(0).play();
                if ($('#step .slider .slide').hasClass('openslide')) {
                    if (num <= $('#step .slider .slide').length) {
                        $('ul.' + $(this).attr("id")).append('<li>' + $(".openslide").text() + '</li>');

                        $('#step .slider .slide:nth-child(' + num + ')').removeClass('openslide').hide();
                        $('#step .slider .slide:nth-child(' + (num + 1) + ')').addClass('openslide').show(); 
                        num++;
                        $('.arrows > .next').fadeOut();
                        $('.arrows > .next').removeClass('open');
                        if ((num - 1) == ($('#step .slider .slide').length)) {
                            $('#Listbreak1').fadeOut(500);
                            $('#Listbreak').fadeIn(500);
                            $('#Listbreak a.next').fadeIn(500);
                            $('#game').get(0).pause();
                            $('#slide21').get(0).currentTime = 0;
                            $('#slide21').get(0).play();

                        }
                    }

                }



            });

        }, 200);
        /*---------------------------------------------------*/
        /*---------------------------------------------------*/
        /*---------------------------------------------------*/
        /*-------------------------------------*/
    });

    $('#sort a.next').click(function () {
        $('#sort').fadeOut(500);
        $('#definitely').fadeIn(500);
        $('#definitely a.next').fadeIn(500);
        $('#slide8').get(0).currentTime = 0;
        $('#slide8').get(0).play();
    });
    $('#definitely a.next').click(function () {
        $('#definitely').fadeOut(500);
        $('#recycle').fadeIn(500);
        $('#recycle a.next').fadeIn(500);
        $('#slide9').get(0).currentTime = 0;
        $('#slide9').get(0).play();
    });
    $('#recycle a.next').click(function () {
        $('#recycle').fadeOut(500);
        $('#compost').fadeIn(500);
        $('#compost a.next').fadeIn(500);
        $('#slide10').get(0).currentTime = 0;
        $('#slide10').get(0).play();
    });
    $('#compost a.next').click(function () {
        $('#compost').fadeOut(500);
        $('#donate').fadeIn(500);
        $('#donate a.next').fadeIn(500);
        $('#slide11').get(0).currentTime = 0;
        $('#slide11').get(0).play();
    });
    $('#donate a.next').click(function () {
        $('#donate').fadeOut(500);
        $('#choseTime').fadeIn(500);
        $('#choseTime a.next').fadeIn(500);
    });
    $('.remind-time label span').click(function () {
        $('#checkbox').get(0).currentTime = 0;
        $('#checkbox').get(0).play();
    });
    $('#choseTime a.next').click(function () {
        $('#choseTime').fadeOut(500);
        $('#reminder1').fadeIn(500);
        $('#reminder1 a.next').fadeIn(500);
    });
    $('#reminder1 a.next').click(function () {
        $('#reminder1').fadeOut(500);
        $('#reminder2').fadeIn(500);
        $('#reminder2 a.next').fadeIn(500);
    });
    $('#reminder2 a.next').click(function () {
        $('#reminder2').fadeOut(500);
        $('#reminder3').fadeIn(500);
        $('#reminder3 a.next').fadeIn(500);
    });

    $('#reminder3 a.next').click(function () {
        $('#reminder3').fadeOut(500);
        $('#Listbreak1').fadeIn(500);
        $('#Listbreak1 a.next').fadeIn(500);
        // $('#knowledge').fadeIn(500);
        // $('#knowledge a.next').fadeIn(500);
        // $('.bkg-image').css('background-image', 'url(content/_assets/Background/BKG_3.png)');
        // $('.bkg-image').css('background-size', '104%');
    });

    $('#Listbreak1 a.next').click(function () {
        $('#Listbreak1').fadeOut(500);
        $('#Listbreak').fadeIn(500);
        $('#Listbreak a.next').fadeIn(500);
        $('#slide22').get(0).currentTime = 0;
        $('#slide22').get(0).play();

        

    });
    $('#Listbreak a.next').click(function () {
        $('#Listbreak').fadeOut(500);
        $('#greenest').fadeIn(500);
        $('#greenest a.next').fadeIn(500);
    });
    $('#greenest a.next').click(function () {
        $('#greenest').fadeOut(500);
        $('#learned').fadeIn(500);
        $('#learned a.next').fadeIn(500);
    });
    $('#learned textarea ').click(function () {
        $('#slide23reminders').get(0).currentTime = 0;
        $('#slide23reminders').get(0).play();

    });
    $('#learned a.next').click(function () {
        $('#learned').fadeOut(500);
        $('#solution').fadeIn(500);
        $('#solution a.next').fadeIn(500);
        $('#slide24').get(0).currentTime = 0;
        $('#slide24').get(0).play();
    });
    $('#solution a.next').click(function () {
        $('#solution').fadeOut(500);
        $('#flip').fadeIn(500);
        
        $('#slide25').get(0).currentTime = 0;
        $('#slide25').get(0).play();
    });
    $('#flip .next.arrow').click(function () {

        $('#flip').fadeOut(500);
        $('#quit').fadeIn(500);

    });
    /////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    $('#noseWords .prev').click(function () {
        $('#noseWords').fadeOut(500);
        $('#home').fadeIn(500);

    });
    $('#noseWords .prev').click(function () {
        $('#game').get(0).play();
        $('#noseWords').fadeOut(500);
        $('#upToUs').fadeIn(500);
        $('#upToUs a.next').fadeIn(500);
    });
    $('#upToUs .prev').click(function () {
        $('#upToUs').fadeOut(500);
        $('#noseWords').fadeIn(500);
    });

    $('#startGame .prev').click(function () {
        $('#startGame').fadeOut(500);
        $('#upToUs').fadeIn(500);
        $('#sort a.next').fadeIn(500);
    });

    // $('#sort a.prev').click(function () {
    //     $('#sort').fadeOut(500);
    //     $('#startGame').fadeIn(500);

    // });
    // $('#definitely a.prev').click(function () {
    //     $('#definitely').fadeOut(500);
    //     $('#sort').fadeIn(500);
    //     $('#definitely a.next').fadeIn(500);
    //     $('#slide8').get(0).currentTime = 0;
    //     $('#slide8').get(0).play();

    // });
    // $('#recycle a.prev').click(function () {
    //     $('#recycle').fadeOut(500);
    //     $('#definitely').fadeIn(500);
    //     $('#recycle a.next').fadeIn(500);
    //     $('#slide9').get(0).currentTime = 0;
    //     $('#slide9').get(0).play();

    // });
    // $('#compost a.prev').click(function () {
    //     $('#compost').fadeOut(500);
    //     $('#recycle').fadeIn(500);
    //     $('#slide10').get(0).currentTime = 0;
    //     $('#slide10').get(0).play();

    // });
    // $('#donate a.prev').click(function () {
    //     $('#donate').fadeOut(500);
    //     $('#compost').fadeIn(500);
    //     $('#compost a.next').fadeIn(500);
    //     $('#slide11').get(0).currentTime = 0;
    //     $('#slide11').get(0).play();
    // });
    // $('.remind-time label span').click(function () {
    //     $('#checkbox').get(0).currentTime = 0;
    //     $('#checkbox').get(0).play();
    // });
    // $('#choseTime a.prev').click(function () {
    //     $('#choseTime').fadeOut(500);
    //     $('#donate').fadeIn(500);
    //     $('#reminder1 a.next').fadeIn(500);
    // });
    // $('#reminder1 a.prev').click(function () {
    //     $('#reminder1').fadeOut(500);
    //     $('#choseTime').fadeIn(500);
    //     $('#reminder2 a.next').fadeIn(500);
    // });
    // $('#reminder2 a.prev').click(function () {
    //     $('#reminder2').fadeOut(500);
    //     $('#reminder1').fadeIn(500);
    //     $('#reminder3 a.next').fadeIn(500);
    // });

    // $('#reminder3 a.prev').click(function () {
    //     $('#reminder3').fadeOut(500);
    //     $('#reminder2').fadeIn(500);

    //     $('.bkg-image').css('background-image', 'url(content/_assets/Background/BKG_2.png)');
    //     $('.bkg-image').css('background-size', '104%');
    // });
    $('#knowledge a.prev').click(function () {
        $('#knowledge').fadeOut(500);
        $('#startGame').fadeIn(500);
        // $('#reminder3').fadeIn(500);
        $('#notebook a.next').fadeIn(500);
        $('.bkg-image').css('background-image', 'url(content/_assets/Background/BKG_2.png)');
        $('.bkg-image').css('background-size', '104%');
    });


    $('#notebook a.prev').click(function () {
        $('#knowledge').fadeIn(500);
        $('#notebook').fadeOut(500);


    });
    // $('#howcouldyou a.prev').click(function () {
    //     $('#howcouldyou').fadeOut(500);
    //     $('#notebook').fadeIn(500);


    // });
    $('#betterway a.prev').click(function () {
        $('#betterway').fadeOut(500);
        $('#notebook').fadeIn(500);
        // $('#howcouldyou').fadeIn(500);
        // $('#slide17-18').get(0).currentTime = 0;
        // $('#slide17-18').get(0).play();

    });
    $('#letslook a.prev').click(function () {
        $('#letslook').fadeOut(500);
        $('#betterway').fadeIn(500);
        $('#slide17-18').get(0).currentTime = 0;
        $('#slide17-18').get(0).play();



    });

    $('#sort a.prev').click(function () {
        $('#sort').fadeOut(500);
        $('#letslook').fadeIn(500);
        $('#slide19').get(0).currentTime = 0;
        $('#slide19').get(0).play();
        // $('#startGame').fadeIn(500);

    });
    $('#definitely a.prev').click(function () {
        $('#definitely').fadeOut(500);
        $('#sort').fadeIn(500);
        $('#definitely a.next').fadeIn(500);
        $('#slide8').get(0).currentTime = 0;
        $('#slide8').get(0).play();

    });
    $('#recycle a.prev').click(function () {
        $('#recycle').fadeOut(500);
        $('#definitely').fadeIn(500);
        $('#recycle a.next').fadeIn(500);
        $('#slide9').get(0).currentTime = 0;
        $('#slide9').get(0).play();

    });
    $('#compost a.prev').click(function () {
        $('#compost').fadeOut(500);
        $('#recycle').fadeIn(500);
        $('#slide10').get(0).currentTime = 0;
        $('#slide10').get(0).play();

    });
    $('#donate a.prev').click(function () {
        $('#donate').fadeOut(500);
        $('#compost').fadeIn(500);
        $('#compost a.next').fadeIn(500);
        $('#slide11').get(0).currentTime = 0;
        $('#slide11').get(0).play();
    });
    $('.remind-time label span').click(function () {
        $('#checkbox').get(0).currentTime = 0;
        $('#checkbox').get(0).play();
    });
    $('#choseTime a.prev').click(function () {
        $('#choseTime').fadeOut(500);
        $('#donate').fadeIn(500);
        $('#reminder1 a.next').fadeIn(500);
    });
    $('#reminder1 a.prev').click(function () {
        $('#reminder1').fadeOut(500);
        $('#choseTime').fadeIn(500);
        $('#reminder2 a.next').fadeIn(500);
    });
    $('#reminder2 a.prev').click(function () {
        $('#reminder2').fadeOut(500);
        $('#reminder1').fadeIn(500);
        $('#reminder3 a.next').fadeIn(500);
    });

    $('#reminder3 a.prev').click(function () {
        $('#reminder3').fadeOut(500);
        $('#reminder2').fadeIn(500);

        // $('.bkg-image').css('background-image', 'url(content/_assets/Background/BKG_2.png)');
        // $('.bkg-image').css('background-size', '104%');
    });

    $('#Listbreak1 a.prev').click(function () {
        $('#Listbreak1').fadeOut(500);
        $('#reminder3').fadeIn(500);
        // $('#letslook').fadeIn(500);
        $('#game').get(0).currentTime = 0;
        $('#game').get(0).play();



    });
    $('#Listbreak a.prev').click(function () {
        $('#Listbreak').fadeOut(500);
        $('#Listbreak1').fadeIn(500);
        $('#slide22').get(0).currentTime = 0;
        $('#slide22').get(0).play();
    });
    $('#greenest a.prev').click(function () {
        $('#greenest').fadeOut(500);
        $('#Listbreak').fadeIn(500);

    });

    $('#learned a.prev').click(function () {
        $('#learned').fadeOut(500);
        $('#greenest').fadeIn(500);


    });
    $('#solution a.prev').click(function () {
        $('#solution').fadeOut(500);
        $('#learned').fadeIn(500);
        $('#slide24').get(0).currentTime = 0;
        $('#slide24').get(0).play();

    });




    (function () {
        var clock = $('.countdown').FlipClock(
            3600*24*3  // here should be set timer for user
            //200
            , {
            'countdown': true,
            "minimumDigits": 2,
            callbacks: {
                stop: function () {
                    console.log('The clock has stopped!');
                    $('#notebook .clock').fadeOut(10);
                    $('#notebook .timeout').fadeIn(500);
                    $('#notebook .hint-popup2').fadeIn(500);
                }
            }
        })
        ;
    })();
    /*-----------------------------------------*/
        // Turn multiple selections on in IE


    /*//////////////////////// OLD scripts for purple box and popups /////////////////////////////*/
   // $('#pop-up').modal('show');



    //to use the close modal, use this function
    $('.modal .no').click(function () {
        $('.modal').modal('hide');
    });
    //to use the close modal, use this function
    /*$('.modal .yes').click(function () {
        function close_window(url) {
            var newWindow = window.open('', '_self', ''); //open the current window
            window.close(url);
        }
        });*/

    $('.close-Btn').click(function () {
        $('#game-info').modal('show');
    });

    

    $('.A').click(function () {

        $("#level-complete").modal('show');



    });

    $('.B').click(function () {

        $("#retry-level").modal('show');



    });

    $('.purple-button').click(function () {
        $('#retry-level').modal('hide')
    });

    $('.close-Btn').click(function () {

        $("#retry-level").modal('show');



    });

    $('.close-Btn').click(function () {

        $("#game-info").modal('hide');



    });


    /*----------------------------------------------------------*/

  
});