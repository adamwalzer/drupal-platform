   $(document).ready(function () {
        try
        {
            start.load();
            start.play();
        }
        catch (err)
        {
            //no sound - log error
        }

        $('#bkg1').css('visibility', 'visible').hide().fadeIn(4000);


        $('#next_btn').click(function () {
            $('#next_btn').delay(1000).delay(1000, function () {
                $("#putcontenthere").load("action_items/ai11.html");
            });
            try
            {
                btn_click.load();
                btn_click.play();
            }
            catch (err) {
                //no sound - log error
            }
        });

    })