<?php

	foreach ($_errors as $_key => $_value) {

		if (strpos($_key, '[') > 0) {

			$_key = preg_replace('/\]/', '', $_key, 1) . ']';

		}

		if (strpos($_value,'Have you forgotten your password?') > 0) {
			$_value = str_replace('The e-mail address','',$_value);
			$_value = str_replace('Have you forgotten your password?','',$_value);
		}

		?>

		$('[name="<?= $_key; ?>"]').each(function(){

			var source = $(this);
			var input1 = source.filter('input[type="text"],input[type="password"]');
			var input2 = source.filter('input[type="checkbox"],input[type="radio"]');

			if (input1.length > 0) {
				input1.val('').attr('placeholder', '<?= addslashes(strip_tags($_value)); ?>');
			}

			if (input2.length > 0) {
				input2.parents('label').addClass('error');
			}

		});

		<?php

	}

?>