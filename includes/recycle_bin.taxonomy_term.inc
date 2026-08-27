<?php

/**
 * @file
 * Taxonomy term storage adapter for Recycle Bin.
 */

/**
 * Taxonomy term controller that turns opted-in deletes into soft deletes.
 */
class RecycleBinTaxonomyTermStorageController extends TaxonomyTermController {
  use RecycleBinStorageAdapterTrait;
}
