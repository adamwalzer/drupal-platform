<?php /* 1.4 */ ?>

<div class="block shadow avatars browse">

	<div class="header">

		<div class="section">
			<h2>Avatars</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<?php if (sizeof($data->items) > 0) { ?>
				<div class="items">
					<?php foreach($data->items as $item) { ?>
						<div class="item">
							<form action="/user/<?php print $data->user->uid; ?>/avatars/browse/add" method="post">
								<input name="nid" type="hidden" value="<?php print $item->nid; ?>" />
								<button type="submit"><img src="<?php print $item->src; ?>" /></button>
							</form>
						</div>
					<?php } ?>
				</div>
			<?php } else { ?>
				<div class="empty">
					There are no avatars.
				</div>
			<?php } ?>
		</div>

	</div>

</div>