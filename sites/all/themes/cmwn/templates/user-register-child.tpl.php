<?php /* Register: Child: Step 1 */ ?>

<?php

	$_node = node_load(11156);
	$_title = $_node->field_custom_title[0]['value'];
	$_subtitle = $_node->field_custom_subtitle[0]['value'];
	$_body = $_node->body;
	$_errors = form_get_errors();

?>

<div class="modal-inner-content step1 child">

	<div class="modal-registration-copy">

		<h1><?php print $_subtitle; ?></h1>
		<?php print $_body; ?>

	</div>

	<div class="modal-registration-form">

		<?php

			unset($form['taxonomy']);

			echo drupal_render($form['field_first_name']);
			echo drupal_render($form['field_last_name']);
			echo drupal_render($form['name']);
			echo drupal_render($form['pass']);
			echo drupal_render($form['mail']);
			echo drupal_render($form['parent_email']);
			echo drupal_render($form['field_dob']);
			echo drupal_render($form['school_code']);
			echo drupal_render($form['field_state']);
			echo drupal_render($form['field_country']);
			echo drupal_render($form['terms_and_conditions']);
			echo drupal_render($form['gender']);
			echo drupal_render($form['submit']);

			echo drupal_render($form);

		?>

	</div>

</div>

<script>

	$(function(){

		if (window.parent && window.parent.modal) {
			window.parent.modal.active(1,false);
		}

		$('#modal-content').css({'height':476}).addClass('tabbed');
		$('#modal-content-inside, .modal-inner-content').css({'height':476});

		$('.form-submit').addClass('modal-button').val('Submit');

		<?php require_once('user-register-validation.tpl.php'); ?>

	});

</script>