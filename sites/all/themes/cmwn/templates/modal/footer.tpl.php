			</div>
		</div>
		<div id="modal-terms-and-conditions">
			<div class="scroll">
				<div class="columns">
					<div class="column">
						<?php
							$_node = node_load(11171);
							$_title = $_node->field_custom_title[0]['value'];
							$_body = $_node->body;
						?>
						<h1><?php print $_title; ?></h1>
						<?php print $_body; ?>
					</div>
					<div class="column">
						<?php
							$_node = node_load(11176);
							$_title = $_node->field_custom_title[0]['value'];
							$_body = $_node->body;
						?>
						<h1><?php print $_title; ?></h1>
						<?php print $_body; ?>
					</div>
				</div>
			</div>
			<div class="close"><a href="close">Close</a></div>
		</div>
	</body>
</html>