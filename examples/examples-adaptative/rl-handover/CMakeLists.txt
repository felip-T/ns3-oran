build_lib_example(
  NAME rl-handover-example
	SOURCE_FILES main.cc oran-logic-module-train-ml-handover.cc open-gym.cc oran-report-sinr-ue.cc oran-reporter-sinr-ue.cc oran-report-trigger-apploss.cc
  LIBRARIES_TO_LINK ${libcore} ${liblte} ${libmobility} ${libbuilds} ${liboran} ${libai} ${libflow-monitor}
  )
