
$(document).ready(function () {
        
        try {
            forest.play();
        }
        catch (err) {
            //no sound - log error
        }


        $('#btn').click(function () {
            $('#btn').delay(1000).delay(1000, function () {
                $("#putcontenthere").load("action_items/ai3.html");
            });
            try {
                click.play();
            }
            catch (err) {
                //no sound - log error
            }
        });
    })