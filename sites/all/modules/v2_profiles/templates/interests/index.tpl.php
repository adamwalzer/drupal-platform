<?php /* 1.4 */ ?>

<div class="block shadow interests index">

	<div class="header">

		<div class="section">
			<h2>Interests</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<?php if (sizeof($data->items->active) > 0) { ?>
				<div class="items">
					<?php foreach ($data->items->active as $item) { ?>
						<div class="item active id-0<?php print $item->id; ?>">
							<?php print $item->title; ?>
						</div>
					<?php } ?>
				</div>
			<?php } else { ?>
				<div class="empty">
					There are no interests.
				</div>
			<?php } ?>
		</div>

	</div>

</div>