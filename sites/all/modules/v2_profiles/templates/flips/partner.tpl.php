<?php /* 1.4 */ ?>

<div class="block shadow flips browse">

	<div class="header">

		<div class="section">
			<h2>Action Items</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<?php if (sizeof($data->items) > 0) { ?>
				<div class="items">
					<?php foreach ($data->items as $item) { ?>
						<div class="<?php print $item->class; ?>">
							<a<?php if($data->user->user_type=='parent') :?> href="<?php print $item->href; ?>"<?php endif; ?>>
								<span class="n1"><img src="<?php print $item->src1; ?>" alt="<?php print $item->title; ?>" /></span>
								<span class="n2" style="height:<?php print $item->progress; ?>%;"><img src="<?php print $item->src2; ?>" alt="<?php print $item->title; ?>" /></span>
							</a>
							<div class="block modal flips description" id="flip-<?php print $item->id; ?>" style="display:none;">
								<div class="content">
									<div class="section cms">
										<?php print $item->description; ?>
									</div>
								</div>
							</div>
						</div>
					<?php } ?>
				</div>
			<?php } else { ?>
				<div class="empty">
					There are no action items.
				</div>
			<?php } ?>
		</div>

	</div>

</div>