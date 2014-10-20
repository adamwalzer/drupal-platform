<?php /* Register: Child: Step 3 */ ?>

<?php

	$_node = node_load(11166);

	$_title = $_node->field_custom_title[0]['value'];
	$_subtitle = $_node->field_custom_subtitle[0]['value'];
	$_body = $_node->body;

?>

<div class="modal-inner-content step3 child">

	<h1><?php print $_subtitle; ?></h1>
	<?php print $_body; ?>
	<p><a href="/user" class="modal-button">Finish</a></p>

</div>

<script>

	$(function(){

		if (window.parent && window.parent.modal) {
			window.parent.modal.active(3,false);
		}

		$('#modal-content').css({'height':476}).addClass('tabbed');
		$('#modal-content-inside, .modal-inner-content').css({'height':476});

		$('.modal-button').bind('click',function(){
			var source = $(this);
			if (window.parent) window.parent.location.href = source.attr('href');
			else window.location.href = source.attr('href');
			return false;
		});

	});

</script>