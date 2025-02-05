build_lib_example(
  NAME simple-db-example
  SOURCE_FILES simple-custom-report.cc oran-reporter-ue-ipv4.cc oran-report-ue-ipv4.cc
  LIBRARIES_TO_LINK ${libcore} ${liblte} ${libmobility} ${libbuilds} ${liboran} ${libflow-monitor}
  )
