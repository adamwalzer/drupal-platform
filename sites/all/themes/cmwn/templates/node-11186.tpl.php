<?php /* Register: Parent: Step 2 */ ?>

<?php

	$_node = node_load(11186);

	$_title = $_node->field_custom_title[0]['value'];
	$_subtitle = $_node->field_custom_subtitle[0]['value'];
	$_body = $_node->body;

?>

<div class="modal-inner-content step2 parent">

	<h1><?php print $_subtitle; ?></h1>
	<?php print $_body; ?>
	<p><a class="modal-button" href="<?php print url('user/'.$user->uid.'/confirm-identity'); ?>">Confirm my Registration</a></p>

</div>

<script>

	$(function(){

		if (window.parent && window.parent.modal) {
			window.parent.modal.active(2,true);
		}

		$('#modal-content').css({'height':559}).addClass('tabbed');
		$('#modal-content-inside, .modal-inner-content').css({'height':559});

	});

</script>