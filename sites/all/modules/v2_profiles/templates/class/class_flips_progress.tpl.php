<div class="block shadow class_flips flips browse index">
  <div class="header">
    <div class="section">
      <h2>Flip Challenge</h2>
    </div>
  </div>

  <div class="content">
      <div class="section">
        <div class="section-left">
          <p class="class-flips-status">Your class earned <?php print count($data->class_flips_progress['complete']); ?> out of <?php print count($data->class_flips_progress['complete']) + count($data->class_flips_progress['incomplete'])?> flips.  <a href="#">View All</a></p>
          <?php
          $flipctr = 0;
          @$isflips = $data->class_flips_progress['complete'];
          if($isflips){
            foreach($data->class_flips_progress['complete'] as $flip){
              print theme('image',ltrim($flip->src2,'/'));
              //print $flip->id;
              $flipctr++;
              if($flipctr > 3){
                break;
              }
            }
          }

          ?>
        </div>

        <div class="section-right">
          <p class="class-flips-start-new">Start a new project.  <a href="#">View All</a></p>
          <?php
          //$flips = v2_profiles_class_unflipped_flips(array_merge(array_keys($data->class_flips_progress['incomplete']), array_keys($data->class_flips_progress['complete'])));
          @$flips = v2_profiles_class_unflipped_flips(array_merge(array_keys($data->class_flips_progress['complete'])));
          $flipctr = 0;
          //print_r($flips);exit;
          if($flips){
            foreach($flips as $flip){
              print theme('image',$flip->field_icon[0]['filepath']);
              //print $flip->nid;
              $flipctr++;
              if($flipctr > 3){
                break;
              }
            }
          }

          ?>
        </div>

      </div>
  </div>
</div>
