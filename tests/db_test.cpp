TEST_CASE("Database load") {
  Database db;
  REQUIRE(db.load_from_file("valid_path.fa") == true);
  REQUIRE(db.find_species("gnome").size() > 0);
}
