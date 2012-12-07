THEME VARIABLES:
This module introduces a coule of extra variables into your page.tpl.php


$alt                  The alt text provided in the image upload field on subsite
                      nodes. field_stanford_subsite_logo. This can be added to
                      the default page.tpl.php markup

$logo_title           The title text provided in the image upload field on
                      subsite nodes. field_stanford_subsite_logo. This can be
                      added to the default page.tpl.php markup

$subsite_logo         A fully rendered image and link tag complete with alt and
                      title text. This variable should replace the $logo
                      variable in page.tpl.php. It falls back to the default
                      $logo image if there is no subsite logo available. This is
                      different from the regular $logo variable as it has alt,
                      title text, and a link that can link to either the subsite
                      page or the drupal root home.

$subsite_site_name    A fully rendered link and site name heading tag. This is
                      different from the regular $site_name page variable as it
                      can have it's link go to either the subsite node or the
                      drupal root home.


