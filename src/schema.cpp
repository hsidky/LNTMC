#include "schema.h"

namespace SAPHRON
{
	//INSERT_DEF_HERE
	std::string SAPHRON::JsonSchema::ForceFields = "{\"items\": {\"oneOf\": [{\"additionalProperties\": false, \"required\": [\"type\", \"sigma\", \"epsilon\", \"rcut\", \"species\"], \"type\": \"object\", \"properties\": {\"sigma\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"numeric\"}, \"type\": {\"enum\": [\"LennardJones\"], \"type\": \"string\"}, \"species\": {\"minItems\": 2, \"items\": {\"type\": \"string\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 2}, \"rcut\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"numeric\"}, \"epsilon\": {\"minimum\": 0, \"type\": \"numeric\"}}}]}, \"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::LennardJones = "{\"additionalProperties\": false, \"required\": [\"type\", \"sigma\", \"epsilon\", \"rcut\", \"species\"], \"type\": \"object\", \"properties\": {\"sigma\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"numeric\"}, \"type\": {\"enum\": [\"LennardJones\"], \"type\": \"string\"}, \"species\": {\"minItems\": 2, \"items\": {\"type\": \"string\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 2}, \"rcut\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"numeric\"}, \"epsilon\": {\"minimum\": 0, \"type\": \"numeric\"}}}";
	std::string SAPHRON::JsonSchema::Worlds = "{\"minItems\": 1, \"items\": {\"required\": [\"type\", \"dimensions\", \"nlist_cutoff\", \"skin_thickness\"], \"type\": \"object\", \"properties\": {\"skin_thickness\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"number\"}, \"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"Simple\"], \"type\": \"string\"}, \"dimensions\": {\"minItems\": 3, \"items\": {\"minimum\": 0, \"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, \"nlist_cutoff\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"number\"}}}, \"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::SimpleWorld = "{\"required\": [\"type\", \"dimensions\", \"nlist_cutoff\", \"skin_thickness\"], \"type\": \"object\", \"properties\": {\"skin_thickness\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"number\"}, \"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"Simple\"], \"type\": \"string\"}, \"dimensions\": {\"minItems\": 3, \"items\": {\"minimum\": 0, \"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, \"nlist_cutoff\": {\"exclusiveMinimum\": true, \"minimum\": 0, \"type\": \"number\"}}}";
	std::string SAPHRON::JsonSchema::Particles = "{\"minItems\": 1, \"items\": {\"minItems\": 4, \"items\": [{\"minimum\": 1, \"type\": \"integer\"}, {\"type\": \"string\"}, {\"type\": \"string\"}, {\"minItems\": 3, \"items\": {\"minimum\": 0, \"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, {\"minItems\": 3, \"items\": {\"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, {\"type\": \"string\"}], \"additionalItems\": false, \"type\": \"array\"}, \"additionalItems\": false, \"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::Site = "{\"minItems\": 4, \"items\": [{\"minimum\": 1, \"type\": \"integer\"}, {\"type\": \"string\"}, {\"type\": \"string\"}, {\"minItems\": 3, \"items\": {\"minimum\": 0, \"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, {\"minItems\": 3, \"items\": {\"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, {\"type\": \"string\"}], \"additionalItems\": false, \"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::Components = "{\"additionalProperties\": false, \"patternProperties\": {\"^[A-z][A-z0-9]+$\": {\"additionalProperties\": false, \"required\": [\"count\"], \"type\": \"object\", \"properties\": {\"count\": {\"minimum\": 1, \"type\": \"integer\"}, \"children\": {\"patternProperties\": {\"^[A-z][A-z0-9]+$\": {\"type\": \"object\"}}, \"type\": \"object\"}}, \"minProperties\": 1}}, \"type\": \"object\", \"minProperties\": 1}";
	std::string SAPHRON::JsonSchema::Selector = "{}";
	std::string SAPHRON::JsonSchema::Director = "{\"minItems\": 3, \"items\": {\"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}";
	std::string SAPHRON::JsonSchema::Observer = "{\"oneOf\": [{\"required\": [\"file_prefix\"], \"properties\": {\"file_prefix\": {\"type\": \"string\"}}}], \"type\": \"object\", \"properties\": {\"frequency\": {\"minimum\": 1, \"type\": \"integer\"}, \"flags\": {\"type\": \"object\", \"properties\": {\"temperature\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"world_density\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"energy\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"acceptance\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"sweeps\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"pressure\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"world_count\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"identifier\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"world_composition\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}, \"world_volume\": {\"minimum\": 0, \"type\": \"integer\", \"maximum\": 1}}}}}";
	std::string SAPHRON::JsonSchema::CSVObserver = "{\"required\": [\"file_prefix\"], \"properties\": {\"file_prefix\": {\"type\": \"string\"}}}";
	std::string SAPHRON::JsonSchema::TranslateMove = "{\"additionalProperties\": false, \"required\": [\"type\", \"dx\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"Translate\"], \"type\": \"string\"}, \"dx\": {\"minimum\": 0, \"type\": \"number\"}}}";
	std::string SAPHRON::JsonSchema::SphereUnitVectorMove = "{\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"SphereUnitVector\"], \"type\": \"string\"}}}";
	std::string SAPHRON::JsonSchema::SpeciesSwapMove = "{\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"type\": {\"enum\": [\"SpeciesSwap\"], \"type\": \"string\"}}}";
	std::string SAPHRON::JsonSchema::ParticleSwapMove = "{\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"ParticleSwap\"], \"type\": \"string\"}}}";
	std::string SAPHRON::JsonSchema::Moves = "{\"items\": {\"oneOf\": [{\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"type\": {\"enum\": [\"FlipSpin\"], \"type\": \"string\"}}}, {\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"type\": {\"enum\": [\"IdentityChange\"], \"type\": \"string\"}}}, {\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"ParticleSwap\"], \"type\": \"string\"}}}, {\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"type\": {\"enum\": [\"SpeciesSwap\"], \"type\": \"string\"}}}, {\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"SphereUnitVector\"], \"type\": \"string\"}}}, {\"additionalProperties\": false, \"required\": [\"type\", \"dx\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"Translate\"], \"type\": \"string\"}, \"dx\": {\"minimum\": 0, \"type\": \"number\"}}}, {\"additionalProperties\": false, \"required\": [\"type\", \"dv\"], \"type\": \"object\", \"properties\": {\"dv\": {\"minimum\": 0, \"type\": \"number\"}, \"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"VolumeScale\"], \"type\": \"string\"}}}]}, \"type\": \"array\"}";
	std::string SAPHRON::JsonSchema::IdentityChangeMove = "{\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"type\": {\"enum\": [\"IdentityChange\"], \"type\": \"string\"}}}";
	std::string SAPHRON::JsonSchema::FlipSpinMove = "{\"additionalProperties\": false, \"required\": [\"type\"], \"type\": \"object\", \"properties\": {\"type\": {\"enum\": [\"FlipSpin\"], \"type\": \"string\"}}}";
	std::string SAPHRON::JsonSchema::GibbsNVTEnsemble = "{\"additionalProperties\": false, \"required\": [\"type\", \"temperature\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"GibbsNVT\"], \"type\": \"string\"}, \"temperature\": {\"exclusiveMinimum\": \"true\", \"minimum\": 0, \"type\": \"number\"}, \"sweeps\": {\"minimum\": 1, \"type\": \"integer\"}}}";
	std::string SAPHRON::JsonSchema::NVTEnsemble = "{\"additionalProperties\": false, \"required\": [\"type\", \"temperature\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"NVT\"], \"type\": \"string\"}, \"temperature\": {\"exclusiveMinimum\": \"true\", \"minimum\": 0, \"type\": \"number\"}, \"sweeps\": {\"minimum\": 1, \"type\": \"integer\"}}}";
	std::string SAPHRON::JsonSchema::Ensembles = "{\"oneOf\": [{\"additionalProperties\": false, \"required\": [\"type\", \"temperature\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"NVT\"], \"type\": \"string\"}, \"temperature\": {\"exclusiveMinimum\": \"true\", \"minimum\": 0, \"type\": \"number\"}, \"sweeps\": {\"minimum\": 1, \"type\": \"integer\"}}}, {\"additionalProperties\": false, \"required\": [\"type\", \"temperature\"], \"type\": \"object\", \"properties\": {\"seed\": {\"minimum\": 0, \"type\": \"integer\"}, \"type\": {\"enum\": [\"GibbsNVT\"], \"type\": \"string\"}, \"temperature\": {\"exclusiveMinimum\": \"true\", \"minimum\": 0, \"type\": \"number\"}, \"sweeps\": {\"minimum\": 1, \"type\": \"integer\"}}}]}";
	std::string SAPHRON::JsonSchema::P2SAConnectivity = "{\"additionalProperties\": false, \"required\": [\"type\", \"coefficient\", \"director\", \"selector\"], \"type\": \"object\", \"properties\": {\"coefficient\": {\"type\": \"number\"}, \"director\": {\"minItems\": 3, \"items\": {\"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, \"type\": {\"enum\": [\"P2SA\"], \"type\": \"string\"}, \"selector\": {}}}";
	std::string SAPHRON::JsonSchema::Connectivities = "{\"items\": {\"oneOf\": [{\"additionalProperties\": false, \"required\": [\"type\", \"coefficient\", \"director\", \"selector\"], \"type\": \"object\", \"properties\": {\"coefficient\": {\"type\": \"number\"}, \"director\": {\"minItems\": 3, \"items\": {\"type\": \"number\"}, \"additionalItems\": false, \"type\": \"array\", \"maxItems\": 3}, \"type\": {\"enum\": [\"P2SA\"], \"type\": \"string\"}, \"selector\": {}}}]}, \"type\": \"array\"}";
	
}