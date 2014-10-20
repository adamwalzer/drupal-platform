<?php /* Register: Child: Step 2 */ ?>

<?php

	$_node = node_load(11161);

	$_title = $_node->field_custom_title[0]['value'];
	$_subtitle = $_node->field_custom_subtitle[0]['value'];
	$_body = $_node->body;

?>

<div class="modal-inner-content step2 child">

	<div class="page n0" style="display:block;">
		<?php print $_body; ?>
	</div>

	<div class="page n1" id="page-how-do-you-like-to-spend-your-free-time">
	  <?php print drupal_render($form['submitted']['how_do_you_like_to_spend_your_free_time']); ?>
	</div>

	<div class="page n2" id="page-if-you-wrote-a-book-what-title-would-you-choose">
	  <?php print drupal_render($form['submitted']['if_you_wrote_a_book_what_title_would_you_choose']); ?>
	</div>

	<div class="page n3" id="page-what-do-you-want-to-be-when-you-grow-up">
	  <?php print drupal_render($form['submitted']['what_do_you_want_to_be_when_you_grow_up']); ?>
	</div>

	<div class="page n4" id="page-where-would-you-go-on-vacation">
	  <?php print drupal_render($form['submitted']['where_would_you_go_on_vacation']); ?>
	</div>

	<div class="page n5" id="page-choose-your-adventure">
	  <?php print drupal_render($form['submitted']['choose_your_adventure']); ?>
	</div>

	<div class="progress" style="display:none;">
		<span>1</span>
		<span>2</span>
		<span>3</span>
		<span>4</span>
		<span>5</span>
	</div>

	<input class="modal-button" id="next-js" type="button" value="Next" />
	<input class="modal-button" id="finish" type="submit" value="Finish" />

	<?php

	  drupal_render($form['actions']['submit']);
	  drupal_render($form['submitted']);

	  print drupal_render($form);

	?>

</div>

<script type="text/javascript">

	$("#next").hide();
	$("#finish").hide();

	var currentPage = 0;
	$("#next-js").click(function() {
		hasAtLeastOneChecked = 0;
		$(".page:eq("+currentPage+")").find("input[type=checkbox]").each(function() {
			if($(this).attr("checked") && !hasAtLeastOneChecked) hasAtLeastOneChecked = 1;
		});
		$(".page:eq("+currentPage+")").find("input[type=radio]").each(function() {
			if($(this).attr("checked") && !hasAtLeastOneChecked) hasAtLeastOneChecked = 1;
		});

		if(currentPage==0) hasAtLeastOneChecked = 1;

		if(!hasAtLeastOneChecked) {
			alert("You must choose at least one option.");
		} else {
			//move to next step
			$(".page:eq("+currentPage+")").fadeOut("fast",function() {
				if(currentPage==4) {
					// we are now on the last step
					$("#next-js").hide();
					$("#finish").show();
				}

				currentPage++;
				$(".page:eq("+currentPage+")").fadeIn("fast",function(){
					$('.progress').fadeIn();
					$('.progress span:lt('+currentPage+')').addClass('completed');
				});
			});
		}
	});

</script>

<script>

	$(function(){

		if (window.parent && window.parent.modal) {
			window.parent.modal.active(2,true);
		}

		$('#modal-content').css({'height':476}).addClass('tabbed');
		$('#modal-content-inside, .modal-inner-content').css({'height':506});

		$('.modal-button').css({'bottom':30});

	});

</script>