<?php /* 1.4 */ ?>

<div class="block register child step2 confirmation">

	<div class="header">

		<div class="section">
			<h1>Check Out Your Interest Groups!</h1>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="items">
				<?php foreach ($data->items as $item) { ?>
					<div class="item <?php print $item->class; ?>">
						<?php print $item->title; ?>
					</div>
				<?php } ?>
			</div>
		</div>

	</div>

	<div class="footer">

		<div class="section buttons">
			<a class="button" href="/node/11166">Next</a>
		</div>

	</div>

</div>

<script>

	$(function(){

		if (window.parent && window.parent.modal) {
			window.parent.modal.active(2,false);
		}

		$('#modal-content').css({'height':476}).addClass('tabbed');
		$('.block.register').css({'height':476});

	});

</script>