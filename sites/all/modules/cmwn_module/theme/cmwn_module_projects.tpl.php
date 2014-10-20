<div class="projects">
<?php foreach ($projects as $project) : ?>
  <div class="project<?php echo $project['project']->is_complete ? ' complete' : '';?>">
    <div class="project_title">
      <?php echo l($project['project']->title, 'node/'.$project['project']->nid); ?>
    </div>
    <div class="brand_partner_title">
      <?php echo l(substr($project['partner']->title, 0, 25) == $project['partner']->title ? $project['partner']->title : substr($project['partner']->title, 0, 25).'...', 'node/'.$project['partner']->nid); ?>
    </div>
    <div class="project_completion">
      <?php echo $project['project']->is_complete ? 'Project is Complete' : l('Connect With Others', 'forum/'.$project['project']->field_forum[0]['value']); ?>
    </div>
  </div>
<?php endforeach; ?>
</div>