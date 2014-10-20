$(function(){

	/* formating */

	$('form,input[type="text"],input[type="password"]').attr('autocomplete','off');

	$('.form-item label').each(function(){

		var source = $(this);

		var input = source.parent('.form-item').find('input[type="password"],input[type="text"]');
		var select = source.parent('.form-item').find('select');

		if (input.length > 0) {

			source.find('span').remove();
			source.html(source.html().replace(':',''));

			input.attr('placeholder',source.html());

			source.remove();

		} else if (select.length > 0) {

			source.remove();

		}

	});

	$('input[type=text]').css({'display':'inline','float':'left'}).wrap('<div style="height:30px;overflow:hidden;" />');

	var month = $('select.date-month');
	var month_value = month.val();
	month.find('option:first-child').remove();
	month.prepend('<option selected="selected" value="">Month</option>');
	month.val(month_value);

	var day = $('select.date-day');
	var day_value = day.val();
	day.find('option:first-child').remove();
	day.prepend('<option selected="selected" value="">Day</option>');
	day.val(day_value);

	var year = $('select.date-year');
	var year_value = year.val();
	year.find('option:first-child').remove();
	year.prepend('<option selected="selected" value="">Year</option>');
	year.val(year_value);
	
	var state = $('#edit-field-state-value');
	state.prepend('<option value="">State</option>');
	var state_value = state.find('option[selected="selected"]').val();
	state.val(state_value);

	$('select').selectBox();

	/* tooltips */

	$('.form-item').each(function() {
		$(this).find('.description').prepend('<div class="arrow"></div>');
	});
	
	$(".form-item input").each(function(){

		var source = $(this);
		var parent = source.parents('.form-item');

		source.live('focus',function(){
			parent.find('.description').fadeTo('fast',0,function(){
				$(this).css({'margin-top':-(($(this).height()+42)/2)+'px'});
				$(this).fadeTo('fast',1);
			});			
		});

		source.live('blur',function(){
			parent.find('.description').fadeOut('fast');
		});

		source.blur();

	});

	/* other */

	$("#modal-content").fadeIn("slow");	
	$("#modal-content-inside").fadeIn("fast");

	/* ---------------------------------------------------------------------------------------------------------------------- */
	/* Form Validation ------------------------------------------------------------------------------------------------------ */
	/* ---------------------------------------------------------------------------------------------------------------------- */
	/*
	if($("form").length) {
		$("form").submit(function() {		
			var hasError = 0;
			$(".required").each(function() {
				if($(this).attr("name")) {
					error = validateField($(this));
					if(!hasError && error) {
						hasError = 1;
					}
				}
			});

			if(hasError)  {
				return false;
			} else {
				return true;
			}
		});
	}
	*/

});

function validateField(field) {
	var fieldName = $(field).attr("name");

	var error = 0;

	switch(fieldName) {
		default:
			if($(field).val()=="") error = 1;
			break;
		case "pass[pass2]":
			if($(field).val()!=$("#edit-pass-pass1").val()) {
				error = 1;
				$("#edit-pass-pass2-wrapper").append('<div class="description"><div class="arrow"></div>Your passwords do not match</div>');
			}
			break;
		
	}

	$(field).removeClass("error");
	if(error) {
		$(field).addClass("error");
		// $(field).closest(".form-item").find(".description").fadeIn("fast");
	}
	
	return error;
}

$(window).resize(function() {
	$(".selectBox-dropdown-menu").hide();
});